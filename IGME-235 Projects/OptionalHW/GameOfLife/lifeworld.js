const lifeworld = {

    init(numCols, numRows){
        this.numCols = numCols,
        this.numRows = numRows,
        this.world = this.buildArray();
        this.worldBuffer = this.buildArray();
        this.randomSetup();
    },

    buildArray(){
        let outerArray = [];
        for (let row=0; row<this.numRows; row++){
            let innerArray = [];
            for (let col=0; col<this.numCols; col++){
                innerArray.push(0);
            }
            outerArray.push(innerArray);
        }
        return outerArray;
    },

    randomSetup(){
        for (let row=0; row<this.numRows; row++){
            for (let col=0; col<this.numCols; col++){
                this.world[row][col] = 0;
                if(Math.random() < .1){
                    this.world[row][col] = 1;
                }
            }
        }
    },

    getLivingNeighbors(row, col){
        let neighbors = 0;
        if (!row > 0){
            return 0;
        }
        if (row >= (numRows - 1)){
            return 0;
        }
        if (!col > 0){
            return 0;
        }
        if (col >= (numCols - 1)){
            return 0;
        }
        for (let y = -1; y<2; y++){
            for (let x = -1; x<2; x++){
                neighbors += this.world[row + x][col + y];
            }
        }
        neighbors -= this.world[row][col];
        return neighbors;
    },

    step(){

        for (let col=0; col<this.numCols; col++){
            for (let row=0; row<this.numRows; row++){
                let neighbors = this.getLivingNeighbors(row, col);
                if ((this.world[row][col] == 1) && (neighbors < 2)){
                    this.worldBuffer[row][col] = 0;
                } 
                else if ((this.world[row][col] == 1) && (neighbors > 3)){
                    this.worldBuffer[row][col] = 0;
                } 
                else if ((this.world[row][col] == 0) && (neighbors == 3)){
                    this.worldBuffer[row][col] = 1;
                }
            }
        }
        for (let row=0; row<this.numRows; row++){
            for (let col=0; col<this.numCols; col++){
                let temp = this.worldBuffer[row][col];
                this.world[row][col] = temp;
            }
        }
        //this.randomSetup();
    }

}