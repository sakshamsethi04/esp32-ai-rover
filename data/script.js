let inputmessage = document.getElementById("inputmessage");

document.getElementById("sendbutton").onclick = function send()
{
    fetch("/chat?msg=" + inputmessage.value);
};
const cam=document.getElementById("camera");
async function camera(){
const stream= await navigator.mediaDevices.getUserMedia({
    video:true
});
cam.srcObject=stream
cam.onloadedmetadata=function(){
    canvas.width=cam.videoWidth;
    canvas.height=cam.videoHeight;
    setInterval(Detectblack,2000);

}
}
camera();
const canvas=document.getElementById("canvas");
const ctx=canvas.getContext("2d");
let Prevx=null;
function Detectblack(){
    ctx.drawImage(cam,0,0);
    const image = ctx.getImageData(0, 0, canvas.width, canvas.height);
    let coords_black=[];
for(let i =0; i<image.data.length; i+=4){
    const r=image.data[i]
    const g=image.data[i+1]
    const b=image.data[i+2]
    let pixel=i/4;
    
    if(r<30 && g<30 && b<30){
        let y=Math.floor(pixel/canvas.width);
        let x=pixel%canvas.width;
        coords_black.push([x,y]);
    }
}
let Sumx=0;
let Sumy=0;
if (coords_black.length==0){
    return;
}
for(let i=0; i<coords_black.length; i++){
    Sumx+=coords_black[i][0];
    Sumy+=coords_black[i][1];
    
}
let Avgx=Sumx/coords_black.length;
let Avgy=Sumy/coords_black.length;
if(Prevx==null){
    Prevx=Avgx
    return;
}
if(Avgx-Prevx>10){
    Prevx=Avgx;
    fetch("http://192.168.1.5/movedleft");
}
else if(Avgx-Prevx<-10){
    Prevx=Avgx
    fetch("http://192.168.1.5/movedright");
}
}

