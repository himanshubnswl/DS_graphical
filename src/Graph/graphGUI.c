//
// Created by lhbdawn on 03-10-2025.
//

#include "graphGUI.h"


#include "../helpers/helper.h"
Vertex * vertexList[MAX_ELEMENTS_NUM] = {nullptr};
Vertex * selected_vertex = nullptr;
int V_List_Top = -1;

Vertex * L_Search_Node(Graph_Node * node) {
    size_t i = 0;
    while (i <= V_List_Top) {
        if (vertexList[i]->node == node) {
            return vertexList[i];
        }
        i++;
    }
    return nullptr;
}

void DrawPointyLine(Vector2 start, Vector2 end, float thick, Color color) {
    double rad = Vector2LineAngle(start, end);
    end.x = end.x - (DEFAULT_RADIUS * cos(rad));
    end.y = end.y + (DEFAULT_RADIUS * sin(rad));
    DrawLineEx(start, end, thick, color);

    double distance = ((end.x - start.x) * (end.x - start.x)) + ((end.y - start.y) * (end.y - start.y));
    distance = sqrt(distance);
    //get direction of the vector
    Vector2 direction = {
        .x = (start.x - end.x)/(distance),
        .y = (start.y - end.y)/(distance)};
    //get base of line from where to move
    Vector2 base = Vector2Scale(direction, ARROW_LENGTH);
    base.x = end.x + base.x;
    base.y = end.y + base.y;
    //get perpendicular vector to the initial vector by rotating dir vector to 90deg
    Vector2 dir_per = Vector2Rotate(direction, PI/2);
    dir_per = Vector2Scale(dir_per, ARROW_LENGTH/2);
    //move towards per vector from base vector
    Vector2 p1 = {
        .x = base.x + dir_per.x,
        .y = base.y + dir_per.y};
    //do same but rotate by -90deg
    dir_per = Vector2Rotate(direction, -PI/2);
    dir_per = Vector2Scale(dir_per, ARROW_LENGTH/2);
    Vector2 p2 = {
        .x = base.x + dir_per.x,
        .y = base.y + dir_per.y};

    DrawLineEx(end, p1, thick, color);
    DrawLineEx(end, p2, thick, color);
}

int DrawEdges() {
    for (int k = 0; k <= V_List_Top; k++) {
        for (int i = 0; i <= vertexList[k]->node->outgoing_edges_index; i++) {
            Vertex * dest = L_Search_Node(vertexList[k]->node->outgoing_edges[i].node);
            DrawPointyLine(vertexList[k]->pos, dest->pos , DEFAULT_LINE_THICKNESS, DEFAULT_COLOR);
        }
    }
    return SUCCESS;
}

void Selection_Vertex(Vertex * vertex) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointCircle(GetMousePosition() , vertex->pos, vertex->radius)) {
            vertex->radius = SELECTED_VERT_RADIUS;
            vertex->color = SELECTED_VERT_COLOR;
            selected_vertex = vertex;
            for (int i = 0; i <= V_List_Top; i++) {
                if (vertexList[i] == vertex) continue;
                vertexList[i]->color = DEFAULT_COLOR;
                vertexList[i]->radius = DEFAULT_RADIUS;
            }
        }
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        selected_vertex = nullptr;
        vertex->color = DEFAULT_COLOR;
        vertex->radius = DEFAULT_RADIUS;
    }
}

void Reset_Selected() {
    selected_vertex = nullptr;
    for (int i = 0 ; i <= V_List_Top; i++) {
        vertexList[i]->color = DEFAULT_COLOR;
        vertexList[i]->radius = DEFAULT_RADIUS;
    }
}

void Reposition_Vertex(Vertex * vertex) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointCircle(GetMousePosition(), vertex->pos, (vertex->radius + 20))) {
            Vector2 delta = GetMouseDelta();
            vertex->pos.x = vertex->pos.x + delta.x;
            vertex->pos.y = vertex->pos.y + delta.y;
            return;
        }
    }
}

int DrawGraph() {
    int i = 0;
    DrawEdges();
    while (i <= V_List_Top) {
        DrawCircleV(vertexList[i]->pos, vertexList[i]->radius, vertexList[i]->color);
        DrawCircleLinesV(vertexList[i]->pos, vertexList[i]->radius, BLACK);
        Vector2 text_pos = MeasureTextEx(GetFontDefault(), int_to_chars(vertexList[i]->node->data), TEXT_SIZE, TEXT_SPACING);
        text_pos.x = vertexList[i]->pos.x - (text_pos.x/2);
        text_pos.y = vertexList[i]->pos.y - (text_pos.y/2);
        DrawTextEx(GetFontDefault(), int_to_chars(vertexList[i]->node->data), text_pos, TEXT_SIZE, TEXT_SPACING, BLACK);
        Selection_Vertex(vertexList[i]);
        Reposition_Vertex(vertexList[i]);
        i++;
    }
    return SUCCESS;
}

int Add_Vertex(Vertex * parent, size_t weight, int data) {
    if (parent == nullptr && vertexList[0] != nullptr) {
        return NO_SELECTION;
    }
    else {
        Vertex * new_vertex = malloc(sizeof(Vertex));

        if (parent == nullptr) {
            new_vertex->node = Add_Graph_Node(data, nullptr, weight);
        }
        else {
            new_vertex->node = Add_Graph_Node(data, parent->node, weight);
        }
        if (new_vertex->node == nullptr) {
            free(new_vertex);
            return ADD_ERROR;
        }
        new_vertex->radius = DEFAULT_RADIUS;
        new_vertex->color = DEFAULT_COLOR;
        new_vertex->pos = (Vector2){
            .x = GetRandomValue(10, WINDOW_WIDTH),
            .y = GetRandomValue(10, WINDOW_HEIGHT)};
        vertexList[++V_List_Top] = new_vertex;
        return SUCCESS;
    }
}

int Input_Element_Handler() {
    static char * valueIN  = nullptr;
    static char * weightch = nullptr;
    if (valueIN == nullptr) {
        valueIN = calloc(TEXT_MAX_SIZE, sizeof(char));
    }
    if (weightch == nullptr) {
        weightch = calloc(TEXT_MAX_SIZE, sizeof(char));
    }

    static bool dial_value_show = false;
     int butt_value = -2; //magic number intended
    static bool dial_weight_show = false;
    static int WRresult = -2;

    Rectangle const add_butt = {
        .x = GetScreenWidth() - 129,
        .y = GetScreenHeight() - 106,
        .width = 100,
        .height = 75};


    Rectangle const dial_value = {
        .x = GetScreenWidth() - 230,
        .y = GetScreenHeight() - 250,
        .width = 200,
        .height = 127};
    Rectangle const dial_weight = {
        .x = GetScreenWidth() - 230,
        .y = GetScreenHeight() - 450,
        .width = 200,
        .height = 127};

    if (GuiButton(add_butt, "Add Vertex")) {
        dial_value_show = true;
    }

    if (dial_value_show) {
        butt_value = GuiTextInputBox(dial_value, nullptr, nullptr, "ADD", valueIN , TEXT_MAX_SIZE, nullptr);
    }

    switch(butt_value) {
        case -1:
            return ADD_ERROR;

        case 0:
            dial_value_show = false;
            return SUCCESS;

        case 1:
            dial_weight_show = true;

        default:
            break;
    }

    if (dial_weight_show == true) {
        dial_value_show = false;
        WRresult = GuiTextInputBox(dial_weight, nullptr, nullptr, "ENTER WEIGHT", weightch, TEXT_MAX_SIZE,nullptr);
        if (WRresult == 1) {
            if (chars_to_int(weightch) == NOT_INT)  return NOT_INT;
            if (chars_to_int(valueIN) == NOT_INT) return NOT_INT;
            Add_Vertex(selected_vertex, chars_to_int(weightch), chars_to_int(valueIN));
            *valueIN = '\0';
            *weightch = '\0';
            dial_weight_show = false;
            return SUCCESS;
        }
        else if (WRresult == 0) {
            dial_weight_show = false;
            butt_value = -2;
            return SUCCESS;
        }
    }
}

void debug_mode() {
    static char string[256];
    if (selected_vertex == nullptr) {
        DrawText("No Selection", 20, 20, 20 ,BLACK);
    }
    else {
        sprintf(string, "Selected Node is: %d", selected_vertex->node->data);
        DrawText(string, 10,10,20,BLACK);
    }
    if (int_to_chars(V_List_Top) == nullptr) {
        DrawText("Nullptr", 50, 50, 20, BLACK);
    }
    else {
        sprintf(string, "Value of V_List_Top is: %d", V_List_Top);
        DrawText(string, 10, 50, 20, BLACK);
    }
}

bool Delete_Vertex_From_List(Vertex * vertex) {
    for (int i = 0 ; i <= V_List_Top; i++) {
        if (vertexList[i] == vertex) {
            for (int j = i ; j < V_List_Top; j++) {
                vertexList[j] = vertexList[j+1];
            }
            vertexList[V_List_Top] = nullptr;
            V_List_Top--;
            free(vertex->node);
            free(vertex);
        }
    }
    return true;
}

int Remove_Element_Handler() {
    static enum ERROR_HANDLER err = SUCCESS;

    Rectangle const removeButton = {
        .x = (GetScreenWidth() - 243),
        .y = (GetScreenHeight() - 106),
        .width = 100,
        .height = 75
    };

    if (GuiButton(removeButton, "Remove Vertex")) {
        if (selected_vertex != nullptr) {
            Remove_Graph_Node(selected_vertex->node);
            for (int i = 0 ; i <= V_List_Top ; i++) {
                if (vertexList[i]->node->data == NON_VALID_NODE_VAL) {
                    Delete_Vertex_From_List(vertexList[i]);
                    i--;
                    err = SUCCESS;
                }
            }
            Reset_Selected();
        }
        else err = REMOVE_ERROR;
    }
    return err;
}

void show_notif(Rectangle bounds, char * text) {
    int prevsize = GuiGetStyle(DEFAULT, TEXT_SIZE);
    GuiSetStyle(DEFAULT, TEXT_SIZE, NOTIF_FONT_SIZE);
    GuiTextBox(bounds, text, TEXT_SIZE, false);
    GuiSetStyle(DEFAULT, TEXT_SIZE, prevsize);
}

int Add_Edge(int weight) {
    Vertex * parent = nullptr;
    Vertex * child = nullptr;
    size_t num_selected = 0;
    while (parent != nullptr && child != nullptr) {
        if (selected_vertex != nullptr) {
            if (num_selected == 0) {
                parent = selected_vertex;
                parent->color = BLUE;
                num_selected++;
            }
            else {
                child = selected_vertex;
                child->color = BLUE;
            }
        }
    }
    Add_Graph_Edge(parent->node, child->node, weight);
}

int Add_Edge_Handler() {
    Rectangle const button = {
        .x = GetScreenWidth() - 355,
        .y = GetScreenHeight() - 106,
        .width = 100,
        .height = 75};
    Rectangle const input_box = {
        .x = GetScreenWidth() - 473,
        .y = GetScreenHeight() - 250,
        .width = 200,
        .height = 127};

    static char edge_val[21] = {'\0'};
    static bool input_box_show = false;
    if (GuiButton(button, "Add Edge")) {
        input_box_show = true;
    }
    if (input_box_show) {
        int result = GuiTextInputBox(input_box, nullptr, nullptr, "Add Edge", edge_val, 20, nullptr);

        switch (result) {
            case 0:
                input_box_show = false;
                return SUCCESS;

            case 1:
                Add_Edge(chars_to_int(edge_val));
                break;
            case -1:
                return ADD_ERROR;
        }
    }
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "graphGUI");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        Input_Element_Handler();
        Remove_Element_Handler();
        DrawGraph();
        Add_Edge_Handler();
        debug_mode();
        EndDrawing();
    }
}

