a =100;
figure;
plot(data{1:101,2}, data{1:101,3},'.',data{102:202,2}, data{102:202,3},'.',data{203:303,2}, data{203:303,3},'.',data{304:404,2}, data{304:404,3},'.',data{405:505,2}, data{405:505,3},'.',data{506:606,2}, data{506:606,3},'.',data{607:707,2}, data{607:707,3},'.',data{708:808,2}, data{708:808,3},'.',data{809:909,2}, data{809:909,3},'.',data{910:1010,2}, data{910:1010,3},'.');
legend('Vgs=0.5V','Vgs=1V','Vgs=1.5V','Vgs=2.0V','Vgs=2.5V','Vgs=3.0V','Vgs=3.5V','Vgs=4.0V','Vgs=4.5V','Vgs=5.0V')
xlabel("Vds (V)");
ylabel("Ids (A)");
title("Ids V Vds");
