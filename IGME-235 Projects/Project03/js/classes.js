class Ship extends PIXI.Sprite {
    constructor(x = 0, y = 0) {
        super(app.loader.resources["images/spaceship.png"].texture);
        this.anchor.set(.5, .5);
        this.scale.set(0.075);
        this.x = x;
        this.y = y;
    }
}
class Bullet extends PIXI.Graphics{
    constructor(color = 0xFFFFFF, x = 0, y = 0, rotation = 0){
        super();
        this.beginFill(color);
        this.drawRect(-2, -3, 4, 6);
        this.endFill();
        this.x = x;
        this.y = y;
        this.rotation = rotation;
        //variables
        this.speed = 400;
        this.isAlive = true;
        Object.seal(this);
    }

    move(dt=1/60){
        this.x += Math.cos(this.rotation - (90 * (Math.PI/180))) * this.speed * dt;
        this.y += Math.sin(this.rotation - (90 * (Math.PI/180))) * this.speed * dt;
    }
}
class Drill extends PIXI.Sprite{
    constructor(x = 0, y = 0){
        super(app.loader.resources["images/spaceship.png"].texture);
        this.anchor.set(.5, .5);
        this.scale.set(0.06);
        this.x = x;
        this.y = y;
        //variables
        this.active = false;
    }
}

class Circle extends PIXI.Graphics{
    constructor(color = 0x000000, x = 0, y = 0, size = Math.random() * 10, fwd = getRandomUnitVector()){
        super();
        
        //this.radius = math.random() * 20;
        this.size = size;
        if (this.size <= 3.5){this.radius = 5.5; this.health = 1; this.threat = 1; this.oreChance = 15;}
        else if (this.size <= 8.5){this.radius = 12; this.health = 2; this.threat = 2; this.oreChance = 8;}
        else if (this.size <= 10){this.radius = 18; this.health = 3; this.threat = 3; this.oreChance = 2;}
        this.beginFill(color);
        this.drawCircle(0, 0, this.radius);
        this.endFill();
        this.x = x;
        this.y = y;
        if (Math.random() * 100 <= this.oreChance){
            this.isOre = true;
        }
        //this.radius = radius;
        //variables
        this.fwd = fwd;
        this.isAlive = true;

        this.speed = (Math.random() * 40) ;

    }
    move(dt=1/60){
        this.x += this.fwd.x * this.speed * dt;
        this.y += this.fwd.y * this.speed * dt;
    }
    damaged(dmg){
        this.health -= dmg;
        if (this.health <= 0){
            this.isAlive = false;
        }
    }
}
class GoldOre extends PIXI.Sprite{
    constructor(x = 0, y = 0, hitbox){
        super(app.loader.resources["images/goldNugget.png"].texture);
        this.anchor.set(.5, .5);
        this.scale.set(0.027 * hitbox.threat);
        this.hitbox = hitbox;
        this.x = x;
        this.y = y;
        this.isAlive = true;
        this.rotationChanger = (Math.random()/2 - 0.25) * (Math.PI/720);
    }
    move(){
        this.x = this.hitbox.x;
        this.y = this.hitbox.y;
        this.rotation = this.rotation + this.rotationChanger;
    }
}

class Alien extends PIXI.Sprite{
    constructor(x = 0, y = 0){
        super(app.loader.resources["images/spaceship.png"].texture);
        this.anchor.set(.5, .5);
        this.scale.set(0.08);
        this.x = x;
        this.y = y;
        this.rotation = Math.random() * 360 - 180;
        //variables
        this.mode = 0;
        this.health = 4;
        this.isAlive = true;
        this.speed = .7;
        this.distance;
        this.lastSeenX;
        this.lastSeenY;
        this.blasterCooldown = 0;
        this.obstacleCooldown = 0;
    }
    moveTowards(target){
        this.distance = parseInt(Math.hypot((this.x-target.x), (this.y-target.y)));
        if (this.mode == 0){
            this.speed = 0;
            if (this.distance <= 95){
                this.blasterCooldown = 90;
                this.mode = 1;
            }
        }
        if (this.mode == 1){
            if (this.distance <= 190){
                if (this.obstacleCooldown > 0){this.obstacleCooldown -= 1;}
                if (this.obstacleCooldown <= 0){this.obstacleCooldown = 0; this.speed = .7; this.rotation = (Math.atan2((this.y - target.y),(this.x - target.x)) - (90 * (Math.PI/180)));}
                if (this.blasterCooldown > 0){this.blasterCooldown -= 1;}
                if (this.blasterCooldown <= 0){this.blasterCooldown = 0;}
                this.lastSeenX = target.x;
                this.lastSeenY = target.y;
                if (this.distance  <= 75){
                    this.speed = parseInt(this.speed/2);
                }
            }
            if (!(this.x - this.lastSeenX <= 5 && this.x - this.lastSeenX >= -5 && this.y - this.lastSeenY <= 5 && this.y - this.lastSeenY >= -5)){
                this.x += Math.cos(this.rotation - (90 * (Math.PI/180))) * this.speed;
                this.y += Math.sin(this.rotation - (90 * (Math.PI/180))) * this.speed;
            }
            else{
                this.mode = 0;
            }
        }
    }
    damaged(dmg){
        this.health -= dmg;
        this.mode = 1;
        if (this.health <= 0){
            this.isAlive = false;
        }
    }
}
class EnemyBullet extends PIXI.Graphics{
    constructor(color = 0xFF00FF, x = 0, y = 0, rotation = 0){
        super();
        this.beginFill(color);
        this.drawRect(-2, -3, 4, 6);
        this.endFill();
        this.x = x;
        this.y = y;
        this.rotation = rotation;
        //variables
        this.speed = 400;
        this.isAlive = true;
        Object.seal(this);
    }
    move(dt=1/60){
        this.x += Math.cos(this.rotation - (90 * (Math.PI/180))) * this.speed * dt;
        this.y += Math.sin(this.rotation - (90 * (Math.PI/180))) * this.speed * dt;
    }
}
class Pursuer extends PIXI.Sprite{
    constructor(x = 0, y = 0){
        super(app.loader.resources["images/spaceship.png"].texture);
        this.anchor.set(.5, .5);
        this.scale.set(0.04);
        this.x = x;
        this.y = y;
        this.rotation = Math.random() * 360 - 180;
        //variables
        this.mode = 0;
        this.health = 1;
        this.isAlive = true;
        this.speed = .6;
        this.distance;
        this.obstacleCooldown = 0;
    }
    moveTowards(target){
        this.distance = parseInt(Math.hypot((this.x-target.x), (this.y-target.y)));
        if (this.mode == 0){
            this.speed = 0;
            if (this.distance <= 190){
                this.mode = 1;
            }
        }
        if (this.mode == 1){
            this.rotation = (Math.atan2((this.y - target.y),(this.x - target.x)) - (90 * (Math.PI/180)));
            if (this.obstacleCooldown > 0){this.obstacleCooldown -= 1;}
            if (this.obstacleCooldown <= 0){
                this.obstacleCooldown = 0; 
                this.speed = .6; 
            }
            this.x += Math.cos(this.rotation - (90 * (Math.PI/180))) * this.speed;
            this.y += Math.sin(this.rotation - (90 * (Math.PI/180))) * this.speed;
        }
    }
    damaged(dmg){
        this.health -= dmg;
        this.mode = 1;
        if (this.health <= 0){
            this.isAlive = false;
        }
    }
}

// class bgLayer1 extends PIXI.Sprite {
//     constructor(x = 0, y = 0) {
//         //super(app.loader.resources["images/starlayer1.png"].texture);
//         super(app.loader.resources["images/starlayer1.png"].texture);
//         //this.anchor.set(.5, .5);
//         this.scale.set(.5);
//         this.x = x;
//         this.y = y;
//         this.speed = 0;
//     }
// }
