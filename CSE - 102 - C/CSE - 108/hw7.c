int isStuck(TILES maze[100][100], Coord currentTile){
    int x = currentTile.x;
    int y = currentTile.y;
    
    int leftX = x-1;
    int rightX = x+1;
    
    int upY = y-1;
    int downY = y+1;

    if( maze[leftX][y].type != EMPTY && maze[rightX][y].type != EMPTY &&
        maze[x][upY].type   != EMPTY && maze[x][downY].type  != EMPTY ){

        return 1;
    }else{
        return 0;
    }
}



int isExit(TILES maze[100][100], Coord currentTile){
    int x = currentTile.x;
    int y = currentTile.y;
    
    int leftX = x-1;
    int rightX = x+1;
    
    int upY = y-1;
    int downY = y+1;

    if( maze[leftX][y].type == BORDER || maze[rightX][y].type == BORDER ||
        maze[x][upY].type   == BORDER || maze[x][downY].type  == BORDER ){

        return 1;
    }else{
        return 0;
    }
}


Path shortestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight){
    int x = currentTile.x;
    int y = currentTile.y;
    
    int leftX = x-1;
    int rightX = x+1;
    
    int upY = y-1;
    int downY = y+1;

    Coord nextTile;
    Path pMin, pTemp;
    PATH_TYPE pType = DISTANCE;

    if(path.totalDamage >= TOTAL_LIFE){
        path.totalDistance = MAX_WEIGHT;
        return  path;
    }else if( isStuck(maze, currentTile) ){
        if( isExit(maze, currentTile) ){
            if (path.totalDistance < *minWeight){
                *minWeight = path.totalDistance;
                return path;
            }else{
                path.totalDistance = MAX_WEIGHT;
                return  path;
            }
        }else{
            path.totalDistance = MAX_WEIGHT;
            return  path;
        }
    }else{
        pMin.totalDistance = MAX_WEIGHT;

        if(maze[leftX][y].type == EMPTY){
            nextTile.x = leftX;
            nextTile.y = y;
            addCoord(maze, &path, nextTile, pType);
            pMin = shortestExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
        }
        if(maze[rightX][y].type == EMPTY){
            nextTile.x = rightX;
            nextTile.y = y;
            addCoord(maze, &path, nextTile, pType);
            pTemp = shortestExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
            if(pTemp.totalDistance < pMin.totalDistance)
                pMin = pTemp;
        }
        if(maze[x][upY].type == EMPTY){
            nextTile.x = x;
            nextTile.y = upY;
            addCoord(maze, &path, nextTile, pType);
            pTemp = shortestExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
            if(pTemp.totalDistance < pMin.totalDistance)
                pMin = pTemp;
        }
        if(maze[x][downY].type == EMPTY){
            nextTile.x = x;
            nextTile.y = downY;
            addCoord(maze, &path, nextTile, pType);
            pTemp = shortestExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
            if(pTemp.totalDistance < pMin.totalDistance)
                pMin = pTemp;
        }

        return pMin;
    }
}

Path comfortableExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight){
    int x = currentTile.x;
    int y = currentTile.y;
    
    int leftX = x-1;
    int rightX = x+1;
    
    int upY = y-1;
    int downY = y+1;

    Coord nextTile;
    Path pMin, pTemp;

    PATH_TYPE pType = COMFORT;


    if(path.totalDamage >= TOTAL_LIFE){
        path.totalComfort = MAX_WEIGHT;
        return  path;
    }else if( isStuck(maze, currentTile) ){
        if( isExit(maze, currentTile) ){
            if (path.totalComfort < *minWeight){
                *minWeight = path.totalComfort;
                return path;
            }else{
                path.totalComfort = MAX_WEIGHT;
                return  path;
            }
        }else{
            path.totalComfort = MAX_WEIGHT;
            return  path;
        }
    }else{
        pMin.totalComfort = MAX_WEIGHT;

        if(maze[leftX][y].type == EMPTY){
            nextTile.x = leftX;
            nextTile.y = y;
            addCoord(maze, &path, nextTile, pType);
            pMin = comfortableExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
        }
        if(maze[rightX][y].type == EMPTY){
            nextTile.x = rightX;
            nextTile.y = y;
            addCoord(maze, &path, nextTile, pType);
            pTemp = comfortableExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
            if(pTemp.totalComfort < pMin.totalComfort)
                pMin = pTemp;
        }
        if(maze[x][upY].type == EMPTY){
            nextTile.x = x;
            nextTile.y = upY;
            addCoord(maze, &path, nextTile, pType);
            pTemp = comfortableExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
            if(pTemp.totalComfort < pMin.totalComfort)
                pMin = pTemp;
        }
        if(maze[x][downY].type == EMPTY){
            nextTile.x = x;
            nextTile.y = downY;
            addCoord(maze, &path, nextTile, pType);
            pTemp = comfortableExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
            if(pTemp.totalComfort < pMin.totalComfort)
                pMin = pTemp;
        }

        return pMin;
    }
}

Path safestExit(TILES maze[100][100], Coord currentTile, Path path, int *minWeight){
    int x = currentTile.x;
    int y = currentTile.y;
    
    int leftX = x-1;
    int rightX = x+1;
    
    int upY = y-1;
    int downY = y+1;

    Coord nextTile;
    Path pMin, pTemp;


    PATH_TYPE pType = DANGER;

    if(path.totalDamage >= TOTAL_LIFE){
        path.totalDanger = MAX_WEIGHT;
        return  path;
    }else if( isStuck(maze, currentTile) ){
        if( isExit(maze, currentTile) ){
            if (path.totalDanger < *minWeight){
                *minWeight = path.totalDanger;
                return path;
            }else{
                path.totalDanger = MAX_WEIGHT;
                return  path;
            }
        }else{
            path.totalDanger = MAX_WEIGHT;
            return  path;
        }
    }else{
        pMin.totalDanger = MAX_WEIGHT;

        if(maze[leftX][y].type == EMPTY){
            nextTile.x = leftX;
            nextTile.y = y;
            addCoord(maze, &path, nextTile, pType);
            pMin = safestExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
        }
        if(maze[rightX][y].type == EMPTY){
            nextTile.x = rightX;
            nextTile.y = y;
            addCoord(maze, &path, nextTile, pType);
            pTemp = safestExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
            if(pTemp.totalDanger < pMin.totalDanger)
                pMin = pTemp;
        }
        if(maze[x][upY].type == EMPTY){
            nextTile.x = x;
            nextTile.y = upY;
            addCoord(maze, &path, nextTile, pType);
            pTemp = safestExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
            if(pTemp.totalDanger < pMin.totalDanger)
                pMin = pTemp;
        }
        if(maze[x][downY].type == EMPTY){
            nextTile.x = x;
            nextTile.y = downY;
            addCoord(maze, &path, nextTile, pType);
            pTemp = safestExit(maze, nextTile, path, minWeight);
            removeLastCoord(maze, &path, nextTile, pType);
            if(pTemp.totalDanger < pMin.totalDanger)
                pMin = pTemp;
        }

        return pMin;
    }
}


/***********************************************************/


void addCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType){
    path->coords[path->size] = coord;
    path->size++;
    path->totalDistance += maze[coord.x][coord.y].distance;
    path->totalComfort += maze[coord.x][coord.y].comfortLevel;
    path->totalDanger += maze[coord.x][coord.y].dangerLevel;
    path->totalDamage += maze[coord.x][coord.y].trapDamage;
    maze[coord.x][coord.y].type = USED;

    switch(pType){
        case DISTANCE:
            path->totalDamage += SHORTEST_DAMAGE;
            break;
        case COMFORT:
            path->totalDamage += COMFORTABLE_DAMAGE;
            break;
        case DANGER:
            path->totalDamage += SAFEST_DAMAGE;
            break;
    }

}

void removeLastCoord(TILES maze[100][100], Path *path, Coord coord, PATH_TYPE pType){
    path->size--;
    path->totalDistance -= maze[coord.x][coord.y].distance;
    path->totalComfort -= maze[coord.x][coord.y].comfortLevel;
    path->totalDanger -= maze[coord.x][coord.y].dangerLevel;
    path->totalDamage -= maze[coord.x][coord.y].trapDamage;
    maze[coord.x][coord.y].type = EMPTY;

    switch(pType){
        case DISTANCE:
            path->totalDamage -= SHORTEST_DAMAGE;
            break;
        case COMFORT:
            path->totalDamage -= COMFORTABLE_DAMAGE;
            break;
        case DANGER:
            path->totalDamage -= SAFEST_DAMAGE;
            break;
    }
}



