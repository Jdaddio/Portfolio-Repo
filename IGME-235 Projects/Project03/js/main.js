// We will use `strict mode`, which helps us by having the browser catch many common JS mistakes
// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Strict_mode
"use strict";
const app = new PIXI.Application({
    width: 800,
    height: 800
});
document.body.appendChild(app.view);

// constants
const sceneWidth = app.view.width;
const sceneHeight = app.view.height;	

// pre-load the images
app.loader.
    add([
        "images/spaceship.png",
        "images/explosions.png",
        "images/starlayer1.png",
        "images/starlayer2.png",
        "images/goldNugget.png"
    ]);
app.loader.onProgress.add(e => { console.log(`progress=${e.progress}`) });
app.loader.onComplete.add(setup);
app.loader.load();

// aliases
let stage;

let bgLayer1;
let bgLayer2;
let bgLayer3;

// game variables
let startScene;
let gameScene,ship,shipDes,scoreLabel,gameOverScoreLabel,lifeLabel,distLabel,toolLabel,shootSound,hitSound,fireballSound;
let gameOverScene;

let circles = [];
let circleSprites = [];
let bullets = [];
let aliens = [];
let enemybullets = [];
let pursuers = [];
let explosions = [];
let explosionTextures;
let score = 0;
let life = 100;
let levelNum = 1;
let distance = 0;
let paused = true;
let toolBool = true;
let keys = {};

//let currentFrame;
let spawnCounter = 0;
let fireFrameCounter = 0;
let invulnerableCounter  = 0;
let canFire = false;
let blasterActive = false;
//let boundRectangle;

let SDM; //Spawn Distance Measurer- a point that resets its X or Y value if they have a value over or under ~ +-133
let drill;

function setup() {
	stage = app.stage;
	// #1 - Create the `start` scene
	startScene = new PIXI.Container();
    stage.addChild(startScene);

	// #2 - Create the main `game` scene and make it invisible
    gameScene = new PIXI.Container();
    gameScene.visible = false;
    stage.addChild(gameScene);

	// #3 - Create the `gameOver` scene and make it invisible
    gameOverScene = new PIXI.Container();
    gameOverScene.visible = false;
    stage.addChild(gameOverScene);
	
	// #4 - Create labels for all 3 scenes
    createLabelsAndButtons();

    /////////// BACKGROUND ///////////
    bgLayer1 = createBg(app.loader.resources["images/starlayer2.png"].texture);
    bgLayer2 = createBg(app.loader.resources["images/starlayer2.png"].texture);
    bgLayer3 = createBg(app.loader.resources["images/starlayer2.png"].texture);
    bgLayer1.width = 800;
    bgLayer1.height = 800;
    startScene.addChild(bgLayer1);
    //gameScene.addChild(bgLayer1);



	// #5 - Create ship
	ship = new Ship();
    gameScene.addChild(ship);
    shipDes = new PIXI.Point(400, 400);
    SDM = new PIXI.Point(0, 0);
    drill = new Drill(400, 400);
    drill.tint = 0x556985;

	// #6 - Load Sounds
	shootSound = new Howl({
        src: ['sounds/shoot.wav']
    });
    hitSound = new Howl({
        src: ['sounds/hit.mp3']
    });
    fireballSound = new Howl({
        src: ['sounds/fireball.mp3']
    });
    shootSound.volume(.08);
    hitSound.volume(.08);
    fireballSound.volume(.08);

	// #7 - Load sprite sheet
	explosionTextures = loadSpriteSheet();	
    
	// #8 - Start update loop
	app.ticker.add(gameLoop);

	// #9 - Start listening for click events on the canvas
    //app.view.onclick = useTool;
    app.view.onmousedown = useTool;
    window.addEventListener("mouseup", stopTool);
    app.view.addEventListener("contextmenu", event => event.preventDefault());
	
	// Now our `startScene` is visible
	// Clicking the button calls startGame()

    //Keyboard event handlers
    window.addEventListener("keydown", keysDown);
    window.addEventListener("keyup", keysUp);

    /////////// SPAWNS ASTEROIDS EVERY 10 SECONDS ///////////
    //setInterval(createCircles, 10000);
}

function createLabelsAndButtons(){
    let buttonStyle = new PIXI.TextStyle({
        fill: 0x00ffd9,
        fontSize: 48,
        fontFamily: "Futura"
    });

    //1 - set up `startScene`
    //1A - make top start label
    let startLabel1 = new PIXI.Text("MineShip");
    startLabel1.style = new PIXI.TextStyle({
       fill: 0x00d9ff,
       fontSize: 96,
       fontFamily: "Futura",
       stroke: 0x543dff,
       strokeThickness: 6 
    });
    startLabel1.x = sceneWidth/4;
    startLabel1.y = sceneHeight/4;
    startScene.addChild(startLabel1);

    //1C - make start game button
    let startButton = new PIXI.Text("Journey into the stars");
    startButton.style = buttonStyle;
    startButton.x = 193;
    startButton.y = sceneHeight - 300;
    startButton.interactive = true;
    startButton.buttonMode = true;
    startButton.on("pointerup", startGame);
    startButton.on('pointerover', e => e.target.alpha = 0.7);
    startButton.on('pointerout', e => e.currentTarget.alpha = 1.0);
    startScene.addChild(startButton);


    //2 - Set up `gameScene`
    let textStyle = new PIXI.TextStyle({
       fill: 0xFFFFFF,
       fontSize: 9,
       fontFamily: "Futura",
       stroke: 0x009e00,
       strokeThickness: 1.5
    });

    // boundRectangle = PIXI.Sprite.from(PIXI.Texture.WHITE);
    // boundRectangle.width = sceneWidth;
    // boundRectangle.height = sceneHeight;
    // boundRectangle.tint = 0x00FF00;
    // gameScene.addChild(boundRectangle);

    //2A - make score label
    scoreLabel = new PIXI.Text();
    scoreLabel.style = textStyle;
    scoreLabel.x = 0;
    scoreLabel.y = 0;
    scoreLabel.resolution = 3;
    gameScene.addChild(scoreLabel);
    increaseScoreBy(0);

    //2B - make life label
    lifeLabel = new PIXI.Text();
    lifeLabel.style = textStyle;
    lifeLabel.x = 0;
    lifeLabel.y = 0;
    lifeLabel.resolution = 3;
    gameScene.addChild(lifeLabel);
    decreaseLifeBy(0);

    distLabel = new PIXI.Text();
    distLabel.style = textStyle;
    distLabel.x = 0;
    distLabel.y = 0;
    distLabel.resolution = 3;
    gameScene.addChild(distLabel);

    //2B - make life label
    toolLabel = new PIXI.Text();
    toolLabel.style = textStyle;
    toolLabel.x = 0;
    toolLabel.y = 0;
    toolLabel.resolution = 3;
    gameScene.addChild(toolLabel);
    decreaseLifeBy(0);

    // 3 - set up `gameOverScene`
    // 3A - make game over text
    let gameOverText = new PIXI.Text("You were destroyed");
    textStyle = new PIXI.TextStyle({
        fill: 0xFFFFFF,
        fontSize: 64,
        fontFamily: "Futura",
        stroke: 0xFF0000,
        strokeThickness: 6
    });
    gameOverText.style = textStyle;
    gameOverText.x = 10;
    gameOverText.y = sceneHeight/2 - 160;
    gameOverScene.addChild(gameOverText);

    gameOverScoreLabel = new PIXI.Text();
    gameOverScoreLabel.style = new PIXI.TextStyle({
        fill: 0xFFFFFF,
        fontSize: 32,
        fontFamily: "Futura",
        stroke: 0x009e00,
        strokeThickness: 6 
    });
    gameOverScoreLabel.x = 150;
    gameOverScoreLabel.y = sceneHeight/2 + 50;
    gameOverScene.addChild(gameOverScoreLabel);

    // 3B - make "play again?" button
    let playAgainButton = new PIXI.Text("Play Again?");
    playAgainButton.style = buttonStyle;
    playAgainButton.x = 150;
    playAgainButton.y = sceneHeight - 100;
    playAgainButton.interactive = true;
    playAgainButton.buttonMode = true;
    playAgainButton.on("pointerup",startGame); // startGame is a function reference
    playAgainButton.on('pointerover',e=>e.target.alpha = 0.7); // concise arrow function with no brackets
    playAgainButton.on('pointerout',e=>e.currentTarget.alpha = 1.0); // ditto
    gameOverScene.addChild(playAgainButton);

}

function createBg(texture){
    let tiling = new PIXI.TilingSprite(texture, 270, 270);
    tiling.position.set(0,0);
    gameScene.addChild(tiling);
    return tiling;
}

function startGame(){
    startScene.visible = false;
    gameOverScene.visible = false;
    gameScene.visible = true;
    startScene.removeChild(bgLayer1);
    gameScene.addChild(bgLayer1);
    bgLayer1.width = 800/3;
    bgLayer1.height = 800/3;
    levelNum = 1;
    score = 0;
    life = 100;
    increaseScoreBy(0);
    decreaseLifeBy(0);
    lifeLabel.text = "Ship health: 100/100";
    ship.x = 400;
    shipDes.x = 400;
    ship.y = 400;
    shipDes.y = 400;
    //loadLevel();
    paused = false;
}

// function loadLevel(){
//     //createCircles(levelNum * 5);

//     paused = false;
// }

function increaseScoreBy(value){
    score += value;
    scoreLabel.text = `Ore collected: ${score}`;
}

function decreaseLifeBy(value){
    if (invulnerableCounter <= 0){
        life -= value;
        life = parseInt(life);
        lifeLabel.text = `Ship health: ${life}/100`;
        invulnerableCounter += 160;
        if (ship != null){
            ship.tint = 0xFFCCCD;
            hitSound.play();
        }
    }
}

function createCircles(direction){
    spawnCounter = 0;
    if (distance >= 250 && !paused){
        for (let i=0; i<distance/200; i++){
            let c = new Circle(0x000000);
            if (direction == "right"){c.x = ship.x + Math.random() * 400 + 133; c.y = ship.y + Math.random() * 700 - 350; console.log("CIRCLES-RIGHT");}
            if (direction == "left"){c.x = ship.x - Math.random() * 400 - 133; c.y = ship.y + Math.random() * 700 - 350; console.log("CIRCLES-LEFT");}
            if (direction == "up"){c.y = ship.y - Math.random() * 400 - 133; c.x = ship.x +  Math.random() * 700 - 350; console.log("CIRCLES-UP");}
            if (direction == "down"){c.y = ship.y + Math.random() * 400 + 133; c.x = ship.x +  Math.random() * 700 - 350; console.log("CIRCLES-DOWN");}

            circles.push(c);
            gameScene.addChild(c);

            let g = new GoldOre(c.x, c.y, c);
            if (!c.isOre){g.tint = 0x4540FF;}
            circleSprites.push(g);
            gameScene.addChild(g);
        }
    }
}
function createAliens(direction){
    if (distance/1500 >= 1){
        for (let i=0; i<distance/5500; i++){
            let a = new Alien(0, 0);
            if (direction == "right"){a.x = ship.x + Math.random() * 400 + 133; a.y = ship.y + Math.random() * 700 - 350; console.log("ALIENS-RIGHT");}
            if (direction == "left"){a.x = ship.x - Math.random() * 400 - 133; a.y = ship.y + Math.random() * 700 - 350; console.log("ALIENS-LEFT");}
            if (direction == "up"){a.y = ship.y - Math.random() * 400 - 133; a.x = ship.x +  Math.random() * 700 - 350; console.log("ALIENS-UP");}
            if (direction == "down"){a.y = ship.y + Math.random() * 400 + 133; a.x = ship.x +  Math.random() * 700 - 350; console.log("ALIENS-DOWN");}

            a.tint = 0x8400ff;
            aliens.push(a);
            gameScene.addChild(a);
        }
    }
}
function createPursuers(direction){
    if (distance/500 >= 1){
        for (let i=0; i<distance/4000; i++){
            let p = new Pursuer(0, 0);
            if (direction == "right"){p.x = ship.x + Math.random() * 400 + 133; p.y = ship.y + Math.random() * 700 - 350; console.log("PURSUERS-RIGHT");}
            if (direction == "left"){p.x = ship.x - Math.random() * 400 - 133; p.y = ship.y + Math.random() * 700 - 350; console.log("PURSUERS-LEFT");}
            if (direction == "up"){p.y = ship.y - Math.random() * 400 - 133; p.x = ship.x +  Math.random() * 700 - 350; console.log("PURSUERS-UP");}
            if (direction == "down"){p.y = ship.y + Math.random() * 400 + 133; p.x = ship.x +  Math.random() * 700 - 350; console.log("PURSUERS-DOWN");}

            p.tint = 0xa83220;
            pursuers.push(p);
            gameScene.addChild(p);
        }
    }
}

function useTool(e){
    if (paused) return;
    if (toolBool){
        blasterActive = true;
        if (gameScene.visible == true && canFire){
            let b = new Bullet(0xFFFFFF, ship.x, ship.y, ship.rotation);
            bullets.push(b);
            gameScene.addChild(b);
            shootSound.play();
            canFire = false;
        }
    }
    if (!toolBool){
        drill.active = true;
    }
}
function stopTool(e){
    drill.active = false;
    blasterActive = false;
}
function shootEnemyBullet(enemy){
    if (paused) return;
    if (gameScene.visible == true){
        let e = new EnemyBullet(0xFF00FF, enemy.x, enemy.y, enemy.rotation);
        enemybullets.push(e);
        gameScene.addChild(e);
        if ((enemy.x - ship.x) >= -135 && (enemy.x - ship.x) <= 135 && (enemy.y - ship.y) >= -135 && (enemy.y - ship.y) <= 135){shootSound.play();}
        enemy.blasterCooldown = 200;
    }
}

function loadSpriteSheet(){
    //The 16 animation frames in each row are 64x64 pixels. We are using the second row.
    //http://pixijs.download/release/docs/PIXI.BaseTexture.html

    let spriteSheet = PIXI.BaseTexture.from("images/explosions.png");
    let width = 64;
    let height = 64;
    let numFrames = 16;
    let textures = [];
    for (let i=0; i<numFrames; i++){
        //http://pixijs.download/release/docs/PIXI.texture.html
        let frame = new PIXI.Texture(spriteSheet, new PIXI.Rectangle(i*width, 64, width, height));
        textures.push(frame);
    }
    return textures;
}

function createExplosion(x, y, frameWidth, frameHeight){
    //the animation frames are 64x64 pixels
    let w2 = frameWidth / 2;
    let h2 = frameHeight / 2;
    let expl = new PIXI.AnimatedSprite(explosionTextures);
    expl.x = x - w2;
    expl.y = y - h2;
    expl.animationSpeed = 1 / 7;
    expl.loop = false;
    expl.onComplete = e => gameScene.removeChild(expl);
    explosions.push(expl);
    gameScene.addChild(expl);
    expl.play();
}

/////////// TRACKS KEY STATES ///////////
function keysDown(e){
    console.log(e.keyCode);
    keys[e.keyCode] = true;
    //Single key press events
    if (gameScene.visible == true){
        if( e.keyCode == 27){
            paused = !paused;
        }
        if (e.keyCode == 16){
            toolBool = !toolBool;
            if (!toolBool){
                gameScene.addChild(drill);
            }
            else{
                gameScene.removeChild(drill);
            }
        }
    }
}
function keysUp(e){
    keys[e.keyCode] = false;
}
/////////// TRACKS KEY STATES ///////////

function gameLoop(){
	if (paused) return; // keep this commented out for now
	
    /////////// WRAPS SCREEN ///////////
    stage.position.x = app.renderer.width / 2;
    stage.position.y = app.renderer.height / 2;
    stage.scale.x = 3.0;
    stage.scale.y = 3.0;
    stage.pivot.x = ship.x;
    stage.pivot.y = ship.y;
    /////////// WRAPS SCREEN ///////////

	// #1 - Calculate "delta time"
	let dt = 1/app.ticker.FPS;
    if (dt > 1/12) dt = 1/12;

	// #2 - Move Ship
    if (keys["87"]){shipDes.y -= 1; SDM.y -= 1;} // W key for Up
    if (keys["65"]){shipDes.x -= 1; SDM.x -= 1;} // A key for Left
    if (keys["83"]){shipDes.y += 1; SDM.y += 1;} // S key for Down
    if (keys["68"]){shipDes.x += 1; SDM.x += 1;} // D key for Right
    if (keys["222"]){decreaseLifeBy(100);}
    //lerp (linear interpolate) the x and y values with lerp()
    let amt = 6 * dt;
    let newX = lerp(ship.x, shipDes.x, amt);
    let newY = lerp(ship.y, shipDes.y, amt);

    ship.x = newX;
    ship.y = newY;
    scoreLabel.x = ship.x + 55;
    scoreLabel.y = ship.y - 120;
    lifeLabel.x = ship.x - 120;
    lifeLabel.y = ship.y - 120;
    distLabel.x = ship.x - 120;
    distLabel.y = ship.y - 100;
    distLabel.text = "Distance: " + parseInt(distance/10) + "m";
    toolLabel.x = ship.x - 120;
    toolLabel.y = ship.y - 80;
    if (toolBool){if (blasterActive){toolLabel.text = "Blaster (active)";} else {toolLabel.text = "Blaster (inactive)";}}
    else{if (drill.active){toolLabel.text = "Drill (active)";} else {toolLabel.text = "Drill (inactive)";}}

    //scoreLabel.text = ("x: " + parseInt(ship.x) + " y: " + parseInt(ship.y) + " SDMx: " + parseInt(SDM.x) + " SDMy: " + parseInt(SDM.y) );

    bgLayer1.position.x = ship.x - 133;
    bgLayer1.position.y = ship.y - 133;
    bgLayer1.tilePosition.x = -newX / 1.2;
    bgLayer1.tilePosition.y = -newY / 1.2;
    bgLayer2.position.x = ship.x - 133;
    bgLayer2.position.y = ship.y - 133;
    bgLayer2.tilePosition.x = -newX / 1.7;
    bgLayer2.tilePosition.y = -newY / 1.7;
    bgLayer3.position.x = ship.x - 133;
    bgLayer3.position.y = ship.y - 133;
    bgLayer3.tilePosition.x = -newX / 2.2;
    bgLayer3.tilePosition.y = -newY / 2.2;


    /////////// ROTATES SHIP USING MOUSE ///////////
	let mousePosition = app.renderer.plugins.interaction.mouse.global;
    ship.rotation = (Math.atan2((mousePosition.y - 400),(mousePosition.x - 400)) + (90 * (Math.PI/180)));
    /////////// ROTATES SHIP USING MOUSE ///////////

    distance = parseInt(Math.hypot((400-ship.x), (400-ship.y)));
 
    /////////// SPAWNS CIRCLES AFTER A SET DISTANCE IN ANY DIRECTION ///////////
    if (SDM.x >= 266){SDM.x = 0; createCircles("right"); 
    createAliens("right"); 
    createPursuers("right");}
    if (SDM.x <= -266){SDM.x = 0; createCircles("left"); 
    createAliens("left"); 
    createPursuers("left");}

    if (SDM.y >= 266){SDM.y = 0; createCircles("down"); 
    createAliens("down");
     createPursuers("down");}
    if (SDM.y <= -266){SDM.y = 0; createCircles("up"); 
    createAliens("up");
    createPursuers("up");}
    /////////// SPAWNS CIRCLES AFTER A SET DISTANCE IN ANY DIRECTION ///////////
    
    if (!canFire){fireFrameCounter += 1;}
    if (fireFrameCounter >= 80){canFire = true; fireFrameCounter = 0;}
    if (blasterActive){useTool();}

    spawnCounter += 1;
    if (spawnCounter >= 4000){createCircles("left"); createCircles("right"); createCircles("down"); createCircles("up");}

    invulnerableCounter -= 1;
    if (invulnerableCounter <= 0){invulnerableCounter = 0; ship.tint = 0xFFFFFF;}

    /////////// ROTATES AND POSITIONS THE DRILL ///////////
    drill.position.x = ship.position.x - Math.cos(ship.rotation + (90 * (Math.PI/180))) * 30;
    drill.position.y = ship.position.y - Math.sin(ship.rotation + (90 * (Math.PI/180))) * 30;
    drill.rotation = ship.rotation;
    /////////// ROTATES AND POSITIONS THE DRILL ///////////
    
    ///////////////////////////////////////// MOVEMENT            /////////////////////////////////////////
    /////////////////////////////////////////          &          /////////////////////////////////////////
    /////////////////////////////////////////            BEHAVIOR /////////////////////////////////////////
	//CIRCLE MOVEMENT
	for (let c of circles){
        c.move(dt);
        for (let g of circleSprites){
            g.move();
        }
    }
	//BULLET BEHAVIOR
    for (let b of bullets){
        b.move(dt);
        //Removes out of bounds bullets
        if ((b.x - ship.x) > 135 || (b.y - ship.y) > 135 || (ship.x - b.x) > 135 || (ship.y - b.y) > 135){
            b.isAlive = false;
            gameScene.removeChild(b);
            //console.log("BULLET REMOVED");
        }
    }
    //ALIEN BEHAVIOR
    for (let a of aliens){
        a.moveTowards(ship);
        if (a.blasterCooldown <= 0 && a.distance <= 95){ shootEnemyBullet(a); }
        for (let c of circles){
            if (parseInt(Math.hypot((a.x-c.x), (a.y-c.y))) <= c.radius + 20 && a.obstacleCooldown <= 0){ 
                a.speed = 0.1;
                a.rotation = (Math.atan2((a.y - c.y),(a.x - c.x)) - (90 * (Math.PI/180)));
                shootEnemyBullet(a);
                a.obstacleCooldown = 90;
            }
        }
        //Checks for collisions with the player drill
        if (rectsIntersect(a, drill) && drill.active){
            hitSound.play();
            a.damaged(.1);
            if (a.isAlive == false){
                createExplosion(c.x, c.y, 64, 64);
                gameScene.removeChild(a);
            }
        }
        //Checks for collisions with player bullets
        for (let b of bullets){
            if (rectsIntersect(a, b)){
                hitSound.play();
                a.damaged(1);
                if (a.isAlive == false){
                    fireballSound.play();
                    createExplosion(a.x, a.y, 64, 64);
                    gameScene.removeChild(a);
                }
                gameScene.removeChild(b);
                b.isAlive = false;
            }
        }
        //Removes out of bounds aliens
        if ((a.x - ship.x) > 400 || (a.y - ship.y) > 400 || (ship.x - a.x) > 400 || (ship.y - a.y) > 400){
            a.isAlive = false;
            gameScene.removeChild(a);
            console.log("ALIEN REMOVED");
        }
    }
    //ENEMY BULLET BEHAVIOR
    for (let e of enemybullets){
        e.move(dt);
        if (e.isAlive && rectsIntersect(e, ship)){
            gameScene.removeChild(e);
            e.isAlive = false;
            decreaseLifeBy(15);
        }
        //Removes out of bounds enemy bullets
        if ((e.x - ship.x) > 400 || (e.y - ship.y) > 400 || (ship.x - e.x) > 400 || (ship.y - e.y) > 400){
            e.isAlive = false;
            gameScene.removeChild(e);
            console.log("ENEMYBULLET REMOVED");
        }
    }
	//PURSUER BEHAVIOR
    for (let p of pursuers){
        p.moveTowards(ship);
        for (let b of bullets){
            if (p.isAlive && rectsIntersect(p, b))
            {
                hitSound.play();
                fireballSound.play();
                p.damaged(1);
                if (p.isAlive == false){
                    createExplosion(p.x, p.y, 32, 32);
                    gameScene.removeChild(p);
                }
                gameScene.removeChild(b);
                b.isAlive = false;
            }
        }
        for (let c of circles){
            if (p.isAlive && rectsIntersect(p, c) && p.mode == 1)
            {
                fireballSound.play();
                c.damaged(3);
                if (c.isAlive == false){
                    createExplosion(c.x, c.y, 64, 64);
                    gameScene.removeChild(c);
                }
                p.obstacleCooldown = 80;
                p.speed = .3;
            }
        }
        if (p.isAlive && rectsIntersect(p, ship)){
            fireballSound.play();
            createExplosion(p.x, p.y, 32, 32);
            gameScene.removeChild(p);
            p.isAlive = false;
            decreaseLifeBy(12);
        }
    }
    //CIRCLE BEHAVIOR
    for (let c of circles){
        for (let b of bullets){
            //Checks for bullet/circle collisions
            if (rectsIntersect(c, b)){
                fireballSound.play();

                c.damaged(1);
                if (c.isAlive == false){
                    createExplosion(c.x, c.y, 64, 64);
                    gameScene.removeChild(c);
                }
                gameScene.removeChild(b);
                b.isAlive = false;
            }

        }
        //If a circle and an enemy bullet collide
        for (let e of enemybullets){
            if (rectsIntersect(c, e)){
                fireballSound.play();
                c.damaged(3);
                gameScene.removeChild(c);
                e.isAlive = false;
                gameScene.removeChild(e);
            }
        }
        //checks for collisions with the ship
        if (c.isAlive && rectsIntersect(c, ship)){
            if (!c.isOre){
                gameScene.removeChild(c);
                c.isAlive = false;
            }
            decreaseLifeBy(10 * c.threat);
        }
        // DRILL COLLISION- ONLY IF ACTIVE (holding mouse)
        if (c.isAlive && rectsIntersect(c, drill) && drill.active){
            hitSound.play();
            //fireballSound.play();
            c.damaged(.01);
            shipDes.x += c.fwd.x * c.speed * dt;
            shipDes.y += c.fwd.y * c.speed * dt;
            if (c.isAlive == false){
                if (c.threat == 3 || c.threat == 2){
                    let newC;
                    if (c.threat == 3){ newC = new Circle(0x000000, c.x, c.y, 8.5, c.fwd); }
                    else { newC = new Circle(0x000000, c.x, c.y, 3.5, c.fwd); }
                    if (c.isOre){newC.isOre = true;}
                    circles.push(newC);
                    gameScene.addChild(newC);
                    let newG = new GoldOre(newC.x, newC.y, newC);
                    if (!newC.isOre){newG.tint = 0x4540FF;}
                    circleSprites.push(newG);
                    gameScene.addChild(newG);
                }
                if (c.isOre){increaseScoreBy(1);}
                //createExplosion(c.x, c.y, 64, 64);
                gameScene.removeChild(c);
            }
        }
        //Removes out of bounds circles
        if ((c.x - ship.x) > 400 || (c.y - ship.y) > 400 || (ship.x - c.x) > 400 || (ship.y - c.y) > 400){
            c.isAlive = false;
            gameScene.removeChild(c);
            console.log("CIRCLE REMOVED");
        }
    }
	for (let g of circleSprites){
        if (g.hitbox.isAlive == false){
            g.isAlive == false;
            gameScene.removeChild(g);
        }
    }
	// #6 - Now do some clean up
    //get rid of dead bullets
    bullets = bullets.filter(b => b.isAlive);
    //get rid of dead circles
    circles = circles.filter(c => c.isAlive);

    aliens = aliens.filter(a => a.isAlive);
    // for (let a of aliens){
    //     a.enemybullets = a.enemybullets.filter(e => e.isAlive);
    // }
    enemybullets = enemybullets.filter(e => e.isAlive);

    pursuers = pursuers.filter(p => p.isAlive);

    circleSprites = circleSprites.filter(g => g.isAlive);
    //get rid of explosions
    explosions = explosions.filter(e => e.playing);

    pursuers = pursuers.filter(p => p.isAlive);
	
	// #7 - Is game over?
	if (life <= 0){
        end();
        return;
    }
	
	// // #8 - Load next level
    // if (circles.length == 0){
    //     levelNum ++;
    //     loadLevel();
    // }
}
    ///////////////////////////////////////// MOVEMENT            /////////////////////////////////////////
    /////////////////////////////////////////          &          /////////////////////////////////////////
    /////////////////////////////////////////            BEHAVIOR /////////////////////////////////////////

function end(){
    paused = true;
    
   //gameOverScoreLabel.text = `Your final score: ${score}`;
    gameOverScoreLabel.text = ` Ore collected: ${score}`;

    //clear out level
    circles.forEach(c => gameScene.removeChild(c));
    circles = [];

    bullets.forEach(b => gameScene.removeChild(b));
    bullets = [];

    aliens.forEach(a => gameScene.removeChild(a));
    aliens = [];

    enemybullets.forEach(b => gameScene.removeChild(b));
    enemybullets = [];

    circleSprites.forEach(g => gameScene.removeChild(g));
    circleSprites = [];

    pursuers.forEach(p => gameScene.removeChild(p));
    pursuers = [];

    explosions.forEach(e => gameScene.removeChild(e));
    explosions = [];


    gameOverScene.visible = true;
    gameScene.visible = false;

    stage.position.x = app.renderer.width;
    stage.position.y = app.renderer.height;
    stage.scale.x = 1.0;
    stage.scale.y = 1.0;
    stage.pivot.x = 675;
    stage.pivot.y = 880;
}