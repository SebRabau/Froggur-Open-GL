#include <vector>
#include "common/objloader.hpp"

int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);

if (matches != 6){

       printf("File can't be read by our simple parser :-( Try exporting with other options\n");

       fclose(file);

       return false;
    } 