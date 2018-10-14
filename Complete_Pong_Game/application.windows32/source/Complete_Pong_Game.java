import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class Complete_Pong_Game extends PApplet {

boolean start= false;
boolean play=false;
boolean stop= false;
float p1x=25,p1y=300,pw=20,ph=160,ps=15;
float p2x,p2y=600,pw2=20,ph2=160,b2s=15,p2=0;
boolean up1= false, down1=false;

float bx,by,bxs=8,bys=8,br=30;
int score1=0, score2=0;
int finalscore=3;
public void setup(){
   
 p2x=width-pw-25;
 start=true;
}
public void draw(){
 if(start){
   background(128,0,0);
   textSize(72);
   text("Pong Game",400,600);
   textSize(36);
   text("Press 'p' to play ...",800,1000);
 }else if(play){
   background(0);
   if(up1){
     p1y -=ps;
   }
   if(down1){
     p1y +=ps;
   }
   p1y= constrain(p1y,0,height-ph);
    
    if(score1<2){
     p2y+=bys;
     pw2=20;
     ph2=160;  
   }
   if(score1>=2){  
     p2y= by;
     pw2=20;
     ph2=500;
     p2y= constrain(p2y,0,height-ph2);
   }
   if(p2y<0|| p2y+160>height){
      b2s=-b2s;
    }
   p2y= constrain(p2y,0,height-ph);
   bx+=bxs;
   by+=bys;
   float btp=by;
   float blt=bx;
   float brt=bx+br;
   float bbt=by+br;
   float p1tp= p1y;
   float p1rt=p1x+pw;
   float p1bt=p1y+ph;
   float p2tp= p2y;
   float p2rt=p2x+pw2;
   float p2bt=p2y+ph2;
   if(by<0|| by>height){
     bys=-bys;
   }
   if(blt <p1rt){
    if(btp>p1bt||bbt<p1tp){
      score2++;
      bx=width/2;
      by= height/2;
      if(score2 == finalscore){
        play=false;
        stop=true;
      }
    }else{
      bxs=-bxs;
    }
   }
    if(blt >p2rt){
    if(btp>p2bt||bbt<p2tp){
      score1++;
      bx=width/2;
      by= height/2;
      if(score1 == finalscore){
        play=false;
        stop=true;
        pw2=10;
        ph2=80;
        bys=5;
        bxs=5;
      }
    }else{
      bxs=-bxs;
      p2-=5;
        if(bys<50){
          ps+=0.5f;
          bys+=3;
        }
    }
  }
   
   ellipse(bx,by,br,br);
   rect(p1x,p1y,pw,ph);
   rect(p2x,p2y,pw2,ph2);
   textSize(72);
   text(score1,200,200);
   text(score2,1000,200);
   textSize(36);
   text("Press 'x' to end the game ...",700,1100);
 }else if(stop){
   background(128,0,200);
   textSize(72);
   text("Game Over",400,600);
   textSize(36);
   text("Press space to start the game ...",600,1000);
   ps=15;
   bys=8;
 }
   }
 public void keyPressed(){
  if(start){
    if(key=='p'){
    play=true;
    start=false;
    }
  }else if(play){
    if(key=='x'){
      play=false;
      stop=true;
    }
    if(keyCode==UP){
      up1=true;
    }if(keyCode==DOWN){
      down1= true;
    }
  }else if(stop){
    if(key==' '){
      score1 =0;
      score2 =0;
      stop=false;
      start= true;
    }
  }
}
public void keyReleased(){
  if(play){
    }if(keyCode==UP){
      up1=false;
    }if(keyCode==DOWN){
      down1= false;
    }
  }
  public void settings() {  size(1200,1200); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--present", "--window-color=#666666", "--stop-color=#cccccc", "Complete_Pong_Game" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
