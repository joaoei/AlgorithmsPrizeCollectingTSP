#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <stdlib.h>   

struct v_tuple {
  int prize;
  int penalty;
};

struct solution {
    std::vector<int> v;
    v_tuple values;
};

v_tuple calc_prize_and_penalties (
    const std::vector<int> &prizes, 
    const std::vector<int> &penalties, 
    const std::vector<std::vector<int>> &travel_cost,
    const std::vector<int> &result_p) {

    int sum_penalties = 0;
    int sum_prizes   = 0;

    //Soma todas as penalidades
    for(int i = 0; i < penalties.size(); i++) {
        sum_penalties += penalties[i];
    }

    for(int j = 0; j < result_p.size() - 1; j++) {
        //Soma premio do no na posição j em result
        sum_prizes   += prizes[result_p[j]];
        sum_penalties -= penalties[result_p[j]];
        sum_penalties += travel_cost[ result_p[j] ][ result_p[j+1] ];
    }

    v_tuple value;
    value.prize = sum_prizes;
    value.penalty = sum_penalties;

    return value;
}

bool is_on_list (
    int element,
    const std::vector<int> &v) {

    bool is_element = false;
    int i = 0;

    while ( !is_element && (i < v.size()) ) {
        if (element == v[i]) {
            is_element = true;
        }

        i++;
    }

    return is_element;
}


solution grasp_vns (
    const std::vector<int> &prizes, 
    const std::vector<int> &penalties, 
    const std::vector<std::vector<int>> &travel_cost,
    const double &prize_min) {
    // solução = vazio
    // penalidade = infinito

    // FASE DE CONSTRUÇÃO
    for (int i = 0; i < maxInter; i++) {
        //s - solução parcial = vazio
        // 0 inserido como nó inicial em s 
        
        // todo k não pertencente a s
        for (int i2 = 0; i2 < nos.size(); i2++) {
            // calcula a economia nas inserções
        }

        while (premio < premio_min || existe economia positiva) {
            // LRC - Lista dos vertices com maior economia
            // Dado um alfa selecionar os n mais economicos
            // Selecionar um aleatoriamente
            // s <- s U {v}
            // Recalcula a economia nas inserções
        }


        if (penalidade(s) < penalidade(solucao) ) {
            solucao = s;
            penalidade(solucao) = penalidade(s)
        }
    }

    
    return VNS(
        solucao,
        3,
        prizes,
        penalties, 
        travel_cost,
        prize_min
    );
}

// Metaheurística ADD_STEP
solution ADD_STEP(
    solution s,
    const std::vector<int> &prizes, 
    const std::vector<int> &penalties, 
    const std::vector<std::vector<int>> &travel_cost,
    const double &prize_min) 
{
    // Construção dos vértices que não fazem parte da rota da solução
    std::vector<int> vertices_not_on_solution;
    for (int i = 0; i < prizes.size(); ++i)
    {
        vertices_not_on_solution.push_back(1);
    }

    // Deixando valor 1 apenas nas posições do vector onde o vértice não está na solução
    for (int i = 0; i < s.v.size() - 1; ++i)
    {
        int num_v_sol = s.v[i]
        vertices_not_on_solution[num_v_sol] = 0;
    }

    do {
        /*
         * Calcula a máxima economia positiva considerando a inserção de vértices que 
         * não fazem parte da solução
         */
        int max_positive_econom = 0;
        int v_max_econom = -1;
        int v1_insert = -1;
        int v2_insert = -1;
        for (int i = 0; i < vertices_not_on_solution; ++i)
        {
            if (vertices_not_on_solution[i] == 0) continue;

            int curr_econom;
            for (int j = 0; j < s.v.size() - 1; ++j)
            {
                int sol_edge_cost = travel_cost[ s.v[j] ][ s.v[j+1] ];
                int v_penalty = penalties[i];
                int v1_to_curr_v = travel_cost[ s.v[j] ][ i ];
                int curr_v_to_v2 = travel_cost[ i ][s.v[j+1] ];
                curr_econom = sol_edge_cost + v_penalty - v1_to_curr_v - curr_v_to_v2;

                if (curr_econom > max_positive_econom)
                {
                    max_positive_econom = curr_econom;
                    v_max_econom = i;
                    v1_insert = s.v[j];
                    v2_insert = s.v[j+1];
                }
            }
        }

        if (max_positive_econom < 1) continue;

        // Atualizando solução com o novo vértice a ser inserido na rota
        std::vector<int> new_v_solution;
        bool did_insert_v = false;
        for (int i = 0; i < s.v.size(); ++i)
        {
            new_v_solution.push_back(s.v[i]);
            if (!did_insert_v && s.v.[i] == v1_insert) { 
                new_v_solution.push_back(v_max_econom);
                did_insert_v = true; 
            }
        }
        vertices_not_on_solution[v_max_econom] = 0; // Agora o vértice é parte da solução
        s.v = new_v_solution;
        s.values.prize = s.values.prize + prizes[v_max_econom];
        s.values.penalty = s.values.penalty - max_positive_econom;
    } while(max_positive_econom > 0 || s.values.prize < prize_min );

    return s;
}


solution VNS ( 
    solution s,
    int maxIt, 
    const std::vector<int> &prizes, 
    const std::vector<int> &penalties, 
    const std::vector<std::vector<int>> &travel_cost,
    const double &prize_min) 
{
    int iterations = 0;
    int num_NBHD = 3;
    /* 
        r = numero de vizinhanças

        1 -> Trocar dois vértices da solução
        2 -> Retirar vértice: Escolhe-se, aleatoriamente, 
             um vértice qualquer (que não seja o 0) e faça 
             parte da solução, removendo-o da solução
        3 -> Inserir vértice: Escolhe-se, aleatoriamente, um 
             vértice não faça parte da solução, inserindo-o no final do caminho.
    */

    while (iterations < maxIt) {
        int n = 1;
        
        while (n <= num_NBHD) {
            // Selecione um vizinho s_1 qualquer da vizinhança N_k(s)
            std::vector<int> s_1 = neighbor(s.v, n, prizes);
            
            // Busca local no vizinho obtido no passo anterior
            //s_2 = BUSCA_LOCAL(s_1);
            
            if ( (s_2.values.prize >= prize_min) && s_2.values.penalty < s.values.penalty) {
                s = s_2;
                k = 1;
            } else {
                k++;
            }
        }

        iterations++;
    }

    return s;
}

std::vector<int> neighbor(
    std::vector<int> s, 
    int nbhd,
    std::vector<int> &prizes) 
{
    std::vector<std::vector<int>> solutions;

    int c;

    switch (nbhd) {
        case 1:
            // Gerar vizinhança trocando dois vértices da solução
            c = s.size() - 2;

            while (c > 1) {
                std::vector<int> solution = s;
                
                int v1 = solution[c];
                int v2 = solution[c-1];

                solution[c] = v2;
                solution[c-1] = v1;

                solutions.push_back(solution);

                c--;
            }

            break;
        case 2:
            // Gerar vizinhança retirando um vértice da solução 
            c = s.size() - 2;

            while (c > 0) {
                std::vector<int> solution = s;

                solution.erase(solution.begin()+c);

                solutions.push_back(solution);

                c--;
            }

            break;
        case 3:
            // Gerar vizinhança inserindo um vértice na solução
            for (int i = 1; i < prizes.size(); i++) {
                if ( !is_on_list(i, s) ) {
                    std::vector<int> solution = s;
                    solution[s.size() - 1] = i;
                    solution.push_back(0);
                
                    solutions.push_back(solution);
                }
            }

            break;
    }

    // Caso vazio retorne a solução passada
    if (solutions.size() == 0) {
        return s;
    } 

    // Escolher aleatoriamente uma solução da vizinhança
    // Retornar valor escolhido
    srand((unsigned)time(0));
    int n = rand()%( solutions.size() );
    
    return solutions[n];
}

/* BUSCA LOCAL
solution VND (solution s) {
    // r = n de procedimentos de refinamento
    k = 1;
    while (k < r) {
        // seja s_ um otimo local segundo o k-esimo procedimento de refinamento
        if (penalidade(s_) < penalidade(s)) {
            s = s_;
            k = 1;
        } else {
            k++;
        }
    }

    return s;
}
*/

int main (int argc, char *argv[]) {
/*
    if (argc > 1) {
        std::string file_name = argv[1];
        std::ifstream infile(file_name);
        if(!infile) {
            std::cout << ">>> Unable to open file!\n";
            return EXIT_FAILURE;
        }

        // Pega o nome do arquivo sem diretórios
        std::string file_name_no_path = file_name;
        size_t i = file_name.rfind('/', file_name.length());
        if (i != std::string::npos) {
          file_name_no_path = file_name.substr(i+1, file_name.length() - i);
        }

        std::string line;
        if (file_name_no_path[0] == 'v') { // instancias-1
            std::getline(infile, line);
            std::getline(infile, line);
        }

        int num_vertices = 0;
        // Lê valores dos prêmios
        std::getline(infile, line);
        std::getline(infile, line);
        std::istringstream prizes_line(line);
        int prize;
        std::vector<int> prizes;
        while (prizes_line >> prize) {
            prizes.push_back(prize);
        }
        num_vertices = prizes.size();

        // Lê valores das penalidades
        std::getline(infile, line);
        std::getline(infile, line);
        std::getline(infile, line);
        std::istringstream penalties_line(line);
        int penalty; // valor do vértice
        std::vector<int> penalties;
        while (penalties_line >> penalty) {
            penalties.push_back(penalty);
        }

        if (prizes.size() != penalties.size()) {
            std::cout << ">>> Invalid instance: number of prizes and penalties don't match!" << '\n';
            return EXIT_FAILURE;
        }

        // Ler valores dos vértices
        std::getline(infile, line);
        std::getline(infile, line);
        std::vector<std::vector<int>> edges(num_vertices);
        int edge; // valor do vértice
        int curr_num = 0;
        for (int i = 0; i < num_vertices; ++i) {
            std::getline(infile, line);
            std::istringstream edges_line(line);
            while(edges_line >> edge) {
                edges[i].push_back(edge);
            }
            if (i > 0) {
                if (curr_num != edges[i].size()) {
                    std::cout << ">>> Invalid instance: incorrect number of edges!" << '\n';
                    return EXIT_FAILURE;
                }
            }
            curr_num = edges[i].size();
        }

        ///////////////////////////////////////////////////////
        std::vector<int> partial_sltn (1, 0);

        solution up_limit;
        double alpha = 0.5; // Alfa padrão
        if (argc > 2) { // Passou valor do alfa
            alpha = std::stod(argv[2]);
        }
        int prizes_sum = 0;
        for (int i = 0; i < prizes.size(); ++i) {
            prizes_sum += prizes[i];
        }
        double p_min = alpha * prizes_sum;
        
        int running_num = 3; // Número de vezes que a instância será executada para tirar a média 
        double average_time = 0;
        std::chrono::steady_clock::time_point begin;
        std::chrono::steady_clock::time_point end;
        solution r;
        for(int i = 0; i < running_num; i++) {
            // Medindo o tempo de execução
            begin = std::chrono::steady_clock::now();
            // r = branch_and_bound_alg(prizes, penalties, edges, partial_sltn, up_limit, prizes.size()-1, p_min);
            end = std::chrono::steady_clock::now();
            // average_time += (std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count()) / running_num;
        }

        if (r.values.prize == prizes[0] && r.values.penalty == penalties[0]) {
            std::cout << "\nNo solution found for the input instance!";
        } else {
            std::cout << ">>> Branch and Bound\n";
            std::cout << "Number of vertices\n  " << num_vertices << "\n";
            std::cout << "Minimum prize (alpha = " << alpha << ")\n  " << p_min << "\n\n";

            std::cout << "Travel\n  ";
            for (int i = 0; i < r.v.size() - 1; i++) {
                std::cout << "(" << r.v[i] << "," << r.v[i+1] << ") ";  
            }
            std::cout << "\n";

            std::cout << "Total prizes\n  " << r.values.prize << "\nTotal penalties\n  " << r.values.penalty << "\n";
            std::cout << "Average execution time on " << running_num << " executions (ms)\n  " << average_time << std::endl;
        }
    } else {
        std::cout << "Please, inform the input file name on execution!\n";
        return EXIT_FAILURE;
    }
 */  

    //TESTE DO VNS E FUNÇÃO neighbor
    int myints[] = {0, 1, 3, 5, 0};
    std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

    std::vector<int> s (7, 2);
    std::vector<int> resp = neighbor(fifth, 1, s);

    for (std::vector<int>::iterator it = resp.begin(); it != resp.end(); ++it)
        std::cout << ' ' << *it;

    std::cout << '\n';

    return 0;
}