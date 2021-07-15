
void checkWhite(gBoard *temp, movement *list){
    int i, j;
    for(i=0; i<7; i++){
        for(j=0; j<7; j++){
            if(temp->Board[i][j][0] == 'w'){
                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*can move bot left*/
                    if(temp->Board[i+1][j-1][0] == ' ')
                        regNormalMove(list, i, j, (i+1), (j-1));
                if(((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 )) /*can move bot right*/
                    if(temp->Board[i+1][j+1][0]== ' ')
                        regNormalMove(list, i, j , (i+1), (j+1));
                /*eat moves below */
                /**/
                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check bottom left move */
                    if((temp->Board[i+1][j-1][0] == 'b')|| (temp->Board[i+1][j-1][0] == 'B'))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j-2) >= 0 && (j-2) < 7 )) /*can eat bottom left */
                            if(temp->Board[i+2][j-2][0]== ' ')
                                regEatMove(list, i, j, (i+1), (j-1), (i+2), (j-2));
                if(((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 )) /*check bottom right move*/
                    if((temp->Board[i+1][j+1][0] == 'b')|| (temp->Board[i+1][j+1][0] == 'B'))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))/*can eat bottom right*/
                            if(temp->Board[i+2][j+2][0]== ' ')
                                regEatMove(list, i,j,i+1,j+1,i+2,j+2);
            }

            if(temp->Board[i][j][0] == 'W'){
                /*first part normal moves to blank spot */
                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 )) /*check bottom left*/
                    if(temp->Board[i+1][j-1][0] == ' ')
                        regNormalMove(list, i, j, (i+1), (j-1));
                if(((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check bottom right*/
                    if(temp->Board[i+1][j+1][0] == ' ')
                        regNormalMove(list,i, j, (i+1), (j+1));
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check top left*/
                    if(temp->Board[i-1][j-1][0] == ' ')
                        regNormalMove(list,i, j, (i-1), (j-1));
                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check top right*/
                    if(temp->Board[i-1][j+1][0] == ' ')
                        regNormalMove(list, i, j, (i-1), (j+1));
                /* eat moves below*/

                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check bottom left move */
                    if((temp->Board[i+1][j-1][0] == 'b')|| (temp->Board[i+1][j-1][0] == 'B'))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))
                            if(temp->Board[i+2][j-2][0]== ' ')
                                regEatMove(list, i,j,i+1,j-1,i+2,j-2);
                if(((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check bottom right move*/
                    if(((temp->Board[i+1][j+1][0] == 'b')|| (temp->Board[i+1][j+1][0] == 'B')))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))
                            if(temp->Board[i+2][j+2][0]== ' ')
                                regEatMove(list,i,j,i+1,j+1,i+2,j+2);
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check top left move */
                    if((temp->Board[i-1][j-1][0] == 'b')|| (temp->Board[i-1][j-1][0] == 'B'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))
                            if(temp->Board[i-2][j-2][0]== ' ')
                                regEatMove(list,i,j,i-1,j-1,i-2,j-2);

                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check top right move*/
                    if((temp->Board[i-1][j+1][0] == 'b')|| (temp->Board[i-1][j+1][0] == 'B'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))
                            if(temp->Board[i-2][j+2][0]== ' ')
                                regEatMove(list, i,j,i-1,j+1,i-2,j+2);
            }
        }
    }
}
void checkBlack(gBoard *temp, movement *list){
    int i, j;

    for(i=0; i<7; i++){
        for(j=0; j<7; j++){
            if(temp->Board[i][j][0] == 'b'){
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*can top bot left*/
                    if(temp->Board[i-1][j-1][0] == ' ')
                        regNormalMove(list,i, j, (i-1), (j-1));
                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*can top bot right*/
                    if(temp->Board[i-1][j+1][0]== ' ')
                        regNormalMove(list,i, j, (i-1), (j+1));
                /*remember to put else */
                /**/
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check bottom left move */
                    if((temp->Board[i-1][j-1][0] == 'w')|| (temp->Board[i-1][j-1][0] == 'W'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))/*can eat bottom left */
                            if(temp->Board[i-2][j-2][0]== ' ')
                                regEatMove(list,i,j,i-1,j-1,i-2,j-2);
                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check bottom right move*/
                    if((temp->Board[i-1][j+1][0] == 'w')|| (temp->Board[i-1][j+1][0] == 'W'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j+2) >= 0 && (j+2) < 7 )) /*can eat bottom right*/
                            if(temp->Board[i-2][j+2][0]== ' ')
                                regEatMove(list, i,j,i-1,j+1,i-2,j+2);
            }
            if(temp->Board[i][j][0] == 'B'){
                /*first part normal moves to blank spot */
                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check bottom left*/
                    if(temp->Board[i+1][j-1][0] == ' ')
                        regNormalMove(list, i, j, (i+1), (j-1));
                if(((i+1) >= 0 && (i+1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check bottom right*/
                    if(temp->Board[i+1][j+1][0] == ' ')
                        regNormalMove(list, i, j, (i+1), (j+1));
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check top left*/
                    if(temp->Board[i-1][j-1][0] == ' ')
                        regNormalMove(list,i, j, (i-1), (j-1));
                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 )) /*check top right*/
                    if(temp->Board[i-1][j+1][0] == ' ')
                        regNormalMove(list, i, j, (i-1), (j+1));

                if(((i+1) >= 0 && (i+1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check bottom left move */
                    if((temp->Board[i+1][j-1][0] == 'w')|| (temp->Board[i+1][j-1][0] == 'W'))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))
                            if(temp->Board[i+2][j-2][0]== ' ')
                                regEatMove(list, i,j,i+1,j-1,i+2,j-2);
                if((i+1) >= 0 && (i+1) < 7 && (j+1) >= 0 && (j+1) < 7 )/*check bottom right move*/
                    if((temp->Board[i+1][j+1][0] == 'w')|| (temp->Board[i+1][j+1][0] == 'W'))
                        if(((i+2) >= 0 && (i+2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))
                            if(temp->Board[i+2][j+2][0]== ' ')
                                regEatMove(list, i,j,i+1,j+1,i+2,j+2);
                if(((i-1) >= 0 && (i-1) < 7) && ((j-1) >= 0 && (j-1) < 7 ))/*check top left move */
                    if((temp->Board[i-1][j-1][0] == 'w')|| (temp->Board[i-1][j-1][0] == 'W'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j-2) >= 0 && (j-2) < 7 ))
                            if(temp->Board[i-2][j-2][0]== ' ')
                                regEatMove(list, i,j,i-1,j-1,i-2,j-2);

                if(((i-1) >= 0 && (i-1) < 7) && ((j+1) >= 0 && (j+1) < 7 ))/*check top right move*/
                    if((temp->Board[i-1][j+1][0] == 'w')|| (temp->Board[i-1][j+1][0] == 'W'))
                        if(((i-2) >= 0 && (i-2) < 7) && ((j+2) >= 0 && (j+2) < 7 ))
                            if(temp->Board[i-2][j+2][0]== ' ')
                                regEatMove(list,i,j,i-1,j+1,i-2,j+2);


            }


        }
    }



}
