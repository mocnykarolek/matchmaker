#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAX_INT 2147483647
struct edge;

struct vertex{

    int number;
    edge* relations;
    int color;


};

struct edge{
    vertex* neighbour;
    int matchness;
    edge* next;

};


struct matrixData {
    int** matrix;

    int matrix_count;


};


void dfs(vertex* v, int number){
    
    if(v->color != -1){
        return;
    }
    else{
        
        
        
        v->color = number;
        
        number++;
        edge* r = v->relations;
        while(r != nullptr){
            // r->neighbour->color = (number)%2;
            dfs(r->neighbour, number%2);
            r = r->next;

        }


    }



}

edge* append(edge* first,edge node){
    edge* newNode = (edge*)malloc(sizeof(edge));

    newNode->matchness = node.matchness;
    newNode->neighbour = node.neighbour;
    

    if( first == nullptr){
        newNode->next = nullptr;
        return newNode;
    }else{
        newNode->next = first;
        return newNode;

    }
    
}

void print_relations(vertex* v, int vertex_number){
    
    for (int i = 0; i < vertex_number; i++)
    {
        edge* relation = v[i].relations;
        
        while(relation->next != nullptr){
            printf("Relacja: %d z %d o wadze: %d\n", v[i].number, relation->neighbour->number, relation->matchness);
            relation = relation->next;
        }
        printf("Relacja: %d z %d o wadze: %d\n", v[i].number, relation->neighbour->number, relation->matchness);
            
        


    }
    printf("\n");
    
    

}



vertex* input_alt(int* v_n){

    int vertices_number;
    int potention_edges;
    
    scanf(" %d", &vertices_number);

    scanf(" %d", &potention_edges);

    *v_n = vertices_number;
    vertex *vertices = (vertex*)malloc(sizeof(vertex)* vertices_number );

    for (int i = 0; i < vertices_number; i++)
    {
        vertices[i].number = i+1;
        vertices[i].color = -1;
        vertices[i].relations = nullptr;
    }
    

    
    for (int i = 0; i < potention_edges; i++)
    {
        int v1, v2, matchness;


        scanf(" %d", &v1);
        scanf(" %d", &v2);
        scanf(" %d", &matchness);

        edge edge;
        edge.matchness = matchness;
        edge.next = nullptr;
        edge.neighbour = (vertices+v2-1);
        vertices[v1-1].relations = append(vertices[v1-1].relations, edge);
        edge.neighbour = (vertices + v1 -1);
        vertices[v2-1].relations = append(vertices[v2-1].relations, edge);

    }
    // print_relations(vertices, vertices_number);

    return vertices;

}

matrixData create_matrix(vertex* vertices, int vertices_number){
    int x_count = 0;
    int y_count = 0;

    int **matrix;
    

    for (int i = 0; i < vertices_number; i++)
    {
            if(vertices[i].color == 1){
                x_count++;
            }
            else if(vertices[i].color == 0){
                y_count++;
            }
    }



    int winner_count;

    if(x_count >= y_count)
        winner_count = x_count;
    else 
        winner_count = y_count;


    
    matrix = (int**)malloc(sizeof(int*)*winner_count);

    for (int y = 0; y < winner_count; y++)
    {
        matrix[y] = (int*)malloc(sizeof(int)* winner_count);
        for (int x = 0; x < winner_count; x++)
        {
            matrix[y][x] = 0;
        }
        
    }
    int* x_map = (int*)malloc(sizeof(int)* (vertices_number+1));
    int* y_map = (int*)malloc(sizeof(int)* (vertices_number+1));

    int x_last_index = 0;
    int y_last_index = 0;

    for (int i = 0; i < vertices_number; i++)
    {
        if(vertices[i].color == 1){
            x_map[vertices[i].number] = x_last_index++;
        }
        else if (vertices[i].color == 0){

            y_map[vertices[i].number] = y_last_index++;
            
        }
    }

    for (int y = 0; y < vertices_number; y++)
    {
        if (vertices[y].color == 0){

            edge* edges = vertices[y].relations;
            while(edges != nullptr){
                int number = edges->neighbour->number;
                matrix[y_map[vertices[y].number]][x_map[number]] = edges->matchness;

                edges = edges->next;
            }
        }
    }
    for (int i = 0; i < vertices_number; i++)
    {
        edge* c = vertices[i].relations;
        while(c!= nullptr){
            edge* to_delete = c;
            c = c->next;
            free(to_delete);
        }
    }
    


    free(vertices);
    free(x_map);
    free(y_map);

    return {matrix, winner_count};
}


bool dfs_graph(int** matrix,int* x_val, int* y_val, int*con_x,int*con_y, int size, int x_vertex, bool* visited_x, bool*visited_y, int* calculated_values){

    visited_x[x_vertex] = true;

    for (int y = 0; y < size; y++)
    {
        if(visited_y[y] == false){
            int calc_space = x_val[x_vertex] + y_val[y] - matrix[x_vertex][y];
            if(calc_space < calculated_values[y]) calculated_values[y] = calc_space;
        }

        if(x_val[x_vertex] + y_val[y] == matrix[x_vertex][y] && visited_y[y] == false){
            visited_y[y] = true;
            if(con_y[y] == -1){
                con_y[y] = x_vertex;
                con_x[x_vertex] = y;
                return true;
            }
            else{
                
                bool success = dfs_graph(matrix, x_val, y_val, con_x, con_y, size, con_y[y], visited_x, visited_y, calculated_values);
                if(success){
                    con_y[y] = x_vertex;
                    con_x[x_vertex] = y;
                    return true;
                }
            }

        }

    }
    return false;
}


void hungarian_algorithm(matrixData md){
    int ** matrix = md.matrix;
    int size = md.matrix_count;
    int* x_values = (int*)malloc(sizeof(int)*size);
    int* y_values = (int*)malloc(sizeof(int)*size);
    
    
    
    int *connection_x = (int*)malloc(sizeof(int)*size);
    int *connection_y = (int*)malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++)
    {
        connection_x[i] = -1;
        connection_y[i] = -1;
    }
    
    

    for (int y = 0; y < size; y++)
    {
        int max = 0;
        
        for (int x = 0;x < size; x++)
        {
              if(matrix[y][x] > max){
                max = matrix[y][x];
              }
            
        }
        x_values[y] = max;
        y_values[y] = 0;

    }

    bool *visited_x = (bool*)malloc(sizeof(bool)*size);
    bool *visited_y = (bool*)malloc(sizeof(bool)*size);
    int *calculated_difference = (int*)malloc(sizeof(int)*size);
    for (int j = 0; j < size; j++)
    {
        
        for (int i = 0; i < size; i++)
        {
            visited_x[i] = false;
            visited_y[i] = false;
            calculated_difference[i] = MAX_INT;
        }
        bool success = dfs_graph(matrix, x_values, y_values, connection_x, connection_y, size, j, visited_x, visited_y, calculated_difference);
        if(success == false){
                // liczenie delta i wykonanie na nowo dfs
                // delta
                int delta = MAX_INT;

                for (int y = 0; y < size; y++)
                {
                    if(calculated_difference[y] < delta && visited_y[y] == false) delta = calculated_difference[y];
                    
                }
                for (int i = 0; i < size; i++)
                {
                    if(visited_x[i]) x_values[i] -=delta;
                    if(visited_y[i]) y_values[i] +=delta;
                }
                
                
                j--;
        }
    }


    int total_matching_points = 0;
    for (int i = 0; i < size; i++)
    {
        if(connection_y[i] != -1)
            total_matching_points += matrix[connection_y[i]][i];
    }
    printf("%d ", total_matching_points);
  
    




    for (int i = 0; i < size; i++)
    {
        free(matrix[i]); 
    }
    free(matrix);
    free(calculated_difference);
    free(visited_x);
    free(visited_y);
    free(connection_x);
    free(connection_y);
    free(x_values);
    free(y_values);
    
}


void perform_instance(){

    int vertices_number;

    vertex* vertices = input_alt(&vertices_number);

    for (int i = 0; i < vertices_number; i++)
    {

        dfs(vertices+i, 0);

    }

    matrixData md = create_matrix(vertices, vertices_number);

    hungarian_algorithm(md);

    
    




}



int main(){

    int instance_number;
    scanf(" %d", &instance_number);
    

    for (int i = 0; i < instance_number; i++)
    {
        perform_instance();
    }
    

    return 0;
}