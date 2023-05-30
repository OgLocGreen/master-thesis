%% Parametros de la chapa
Lc = 300; %cm
Hc = 150; %cm

% para generar las imagenes
Xi = Lc+200; %cm
Yi = Hc+200; %cm 
Img = zeros(2*Yi+1, 2*Xi+1);

Img((-Hc:Hc)+Yi, (-Lc:Lc)+Xi )= 1;

imshow(Img);

%% Parametros del robot (Dimensiones en cm)
L_sherpaXL = 44/2;
H_sherpaXL = 58/2;

% L_vulcano = 114/2;
% H_vulcano = 90/2;
% 
% L_max = (Lc - offsetdx)/2;
% H_max = (Hc - offsetdy)/2;

Lr = L_sherpaXL; %min(L_max, H_max);  %80; %cm
Hr = H_sherpaXL; %min(L_max, H_max); % sherpa = 58/2; 50; %cm
% mascara del robot
Imgr = ones( 2*Hr+1, 2*Lr+1);

offsetdx = 0; % 2*Hr;
offsetdy = 0; % 0;


%% Parametros de la herramienta
Xd = (Lr+offsetdx); %cm
Yd = (Hr+offsetdy); %cm
% mascara de la herramienta
Imgd = zeros(2*abs(Yd)+1, 2*abs(Xd)+1);
Imgd(abs(Yd)+1-Yd, abs(Xd)+1+Xd)=1;
% Imgd(1,1) = 1;
%% Zona navegable con ejes paralelos
[A1,A2,A3,A4] = zonareparadaInterior(Img, Imgr, Imgd, 0);
ImgDisp = Img;
ImgDisp(A4==1) = 2;
imagesc(ImgDisp);

%% Zona cubierta cuando el robot gira 90 grados
[B1,B2,B3,B4] = zonareparadaInterior(Img, Imgr, Imgd, 1);

ImgDisp(B4==1 & A4==0) = 3;
imagesc(ImgDisp);

%% Rotacion de 180 grados
[C1,C2,C3,C4] = zonareparadaInterior(Img, Imgr, Imgd, 2);

ImgDisp(C4==1 & (A4+B4)==0) = 4;
imagesc(ImgDisp);

%% Rotacion de 270 grados

[D1,D2,D3,D4] = zonareparadaInterior(Img, Imgr, Imgd, 3);

ImgDisp(D4==1 & (A4+B4+C4)==0) = 5;

figure(1)
imagesc(ImgDisp);
hold on
plot([Xi Xi],[1 2*Yi+1],'r')
plot([1 2*Xi+1],[Yi Yi],'r')
hold off

figure(2)
plot(Lc*[-1 1 1 -1 -1],Hc*[1 1 -1 -1 1],'Color',[0.2667 0.3882 0.9882],'LineWidth',1.5)
axis([-350 350 -200 200])
axis square
axis equal
hold on
% 0 grados
plot([-(Lc-(max(Lr,-Xd)+Xd)) Lc-max(Lr,Xd)+Xd Lc-max(Lr,Xd)+Xd -(Lc-(max(Lr,-Xd)+Xd)) -(Lc-(max(Lr,-Xd)+Xd))],...
     [Hc-max(Hr,Yd)+Yd Hc-max(Hr,Yd)+Yd -(Hc-(max(Hr,-Yd)+Yd)) -(Hc-(max(Hr,-Yd)+Yd)) Hc-max(Hr,Yd)+Yd],...
      'Color',[0.1098 0.6627 0.8745],'LineWidth',1.5)
% 90 grados
plot([-(Lc-(max(Hr,Yd)-Yd)) Lc-max(Hr,-Yd)-Yd Lc-max(Hr,-Yd)-Yd -(Lc-(max(Hr,Yd)-Yd)) -(Lc-(max(Hr,Yd)-Yd))],...
     [Hc-max(Lr,Xd)+Xd Hc-max(Lr,Xd)+Xd -(Hc-(max(Lr,-Xd)+Xd)) -(Hc-(max(Lr,-Xd)+Xd)) Hc-max(Lr,Xd)+Xd],...
      'Color',[0.2902 0.7961 0.5176],'LineWidth',1.5)
% 180 grados
plot([-(Lc-(max(Lr,Xd)-Xd)) Lc-max(Lr,-Xd)-Xd Lc-max(Lr,-Xd)-Xd -(Lc-(max(Lr,Xd)-Xd)) -(Lc-(max(Lr,Xd)-Xd))],...
     [Hc-max(Hr,-Yd)-Yd Hc-max(Hr,-Yd)-Yd -(Hc-(max(Hr,Yd)-Yd)) -(Hc-(max(Hr,Yd)-Yd)) Hc-max(Hr,-Yd)-Yd],...
     'Color',[0.9373 0.7255 0.2078],'LineWidth',1.5)
% 270 grados
plot([-(Lc-(max(Hr,-Yd)+Yd)) Lc-max(Hr,Yd)+Yd Lc-max(Hr,Yd)+Yd -(Lc-(max(Hr,-Yd)+Yd)) -(Lc-(max(Hr,-Yd)+Yd))],...
     [Hc-max(Lr,-Xd)-Xd Hc-max(Lr,-Xd)-Xd -(Hc-(max(Lr,Xd)-Xd)) -(Hc-(max(Lr,Xd)-Xd)) Hc-max(Lr,-Xd)-Xd],...
     'Color',[0.9765 0.9804 0.07843],'LineWidth',1.5)


hold off

%% Borde exterior
% E4 = Img - imerode(Img,ones(2*(Lr-Xd)+1));
% 
% ImgDisp(E4==1) = 6;
% imagesc(ImgDisp);
% axis equal




%% Funciones auxiliares

function [A1, A2, A3, A4] = zonareparadaInterior(Img, Imgr, Imgd, k)
Imgr1 = rot90(Imgr);
Imgd1 = rot90(Imgd);

% Zona navegable sin salirse de la chapa
A1 = imerode(Img, rot90(Imgr, k));

% Posiciones del robot para cubrir la chapa con la herramienta
A2 = imerode(Img, rot90(Imgd,k));
A2(isinf(A2))=0;

% Posiciones del robot para cubrir la chapa sin salirse de la misma.
A3 = A1 & A2;

% Zona 
A4 = imdilate(A3, rot90(Imgd,k)); 

end


function [A1, A2, A3, A4] = zonareparadaExterior(Img, Imgr, Imgd, k)
Imgr1 = rot90(Imgr);
Imgd1 = rot90(Imgd);

A1 = imerode(~Img, rot90(Imgr, k));

A2 = imerode(Img, rot90(Imgd,k));
A2(isinf(A2))=0;

A3 = A1 & A2;

A4 = imdilate(A3, rot90(Imgd,k)); 

end


