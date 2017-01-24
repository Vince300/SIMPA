//Automates in which all vertices are reachable from the starting point (vertex s0)
//
//g++ -std=c++11 -o generate_digraph generate_digraph.cpp
//./generate_digraph 50 20 5 0.2 graph_
//10 automates with 20 vertices with 5 edge attempts with 0.2 probability each in files named auto***.dot
//argv[1] = [1,999]
//argv[2] = [1,99]
//argv[3] = [1,26]
//argv[4] = [0.0,1.0]


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>


void write(std::string filename, long vertices, std::vector<long> *links)
{
    char temp[3], target[3];
    std::string aux;

    aux = filename + ".dot";
    std::ofstream file(aux.c_str(), std::ofstream::out);	
    file << "digraph " << filename << " {\n"; 

    for(long i = 0; i < vertices; ++i)
    {
        char k = 'a';
	sprintf(temp, "%.2ld", i);

        for(long j = 0; j < links[i].size(); ++j)
	{
		sprintf(target, "%.2ld", links[i][j]);
                file << "\ts" << temp << " -> s" << target << " [label=\"" << k++ << "/" << rand() % 2 << "\"];\n";
	}
    }

    file << "\ts00 [shape=doubleoctagon];\n}";

    file.close();
}

bool test(long current, long vertices, std::vector<long> *links, bool *validation)
{
    bool b = true;


    validation[current] = true;


    for(long i = 0; i < vertices && b; ++i)
        if(!validation[i])
            b = false;

    if(b)
        return true;

    for(long i = 0; i < links[current].size(); ++i)
        if(!validation[links[current][i]])
            if(test(links[current][i], vertices, links, validation))
                return true;

    return false;
}

void automata(std::string filename, long probability, long vertices, long edges)
{
    bool c, validation[vertices];


    do
    {
	std::vector<long> links[vertices];


        for(long i = 0; i < vertices; ++i)
        {
            validation[i] = false;

            for(long j = 0; j < edges; ++j)
            {
                long n = rand() % probability;

                if(n < vertices)    
                {
                    bool b;

                    while(true)
                    {
			
                        b = true;

                        for(long k = 0; k < links[i].size() && b; ++k)
                            if(links[i][k] == n)
                                b = false;
			
			if(b)
			    break;
		
			n = rand() % vertices;
                    }

                    links[i].push_back(n);
                }
            }
        }  

	c = test(0, vertices, links, validation); 

	if(c)
		write(filename, vertices, links);   
    }
    while(!c);   
}

int main(int argc, char **argv)
{
    if(argc != 6)
    {
	std::cout << "You must provide 5 arguments." << std::endl;
	return 1;
    }


    long files = atol(argv[1]), vertices = atol(argv[2]), edges = atol(argv[3]), probability = (long) (vertices / atof(argv[4]));


    if(files < 1 || vertices < 1 || vertices > 99 || vertices < edges || edges > 26 || edges < 1 || vertices > probability)
    {
	std::cout << "Logical Error!" << std::endl;
	return 1;
    }

    std::cout << std::endl << argv[4] << " probability for " << edges << " edge attempts for each of " << vertices << " vertices." << std::endl << std::endl;

    srand(time(NULL));
    
    for(long i = 1; i <= files; ++i)
    {
	std::string filename = argv[5];
	char filenumber[4];


	sprintf(filenumber, "%.3ld", i);
    	filename += filenumber;
        automata(filename, probability, vertices, edges);
	std::cout << i << " / " << files << std::endl;
    } 

    std::cout << std::endl;


    return 0;
}
