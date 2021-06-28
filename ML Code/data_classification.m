close all
clc
clear

t = readtable('CondensedData2.csv');

time = table2array(t(:, 'Time'));
angle = table2array(t(:, 'Angle'));
linacc = table2array(t(:, 'LinAcc'));
gravx = table2array(t(:, 'GravX'));
gravy = table2array(t(:, 'GravY'));
gravz = table2array(t(:, 'GravZ'));
linvel1 = table2array(t(:, 'LinVel1'));
linvel2 = table2array(t(:, 'LinVel2'));

figure(1)
plot(time, angle)
hold on
plot(time, linacc)
% plot(time, gravx)
% plot(time, gravy)
% plot(time, gravz)
legend('Angle', 'LinAcc')
xlabel('Time (s)')
ylabel('Angle (degrees)/Linear Acceleration (m/s^2)')

angle_input.time = time;
angle_input.signals.values = angle-mean(angle);
linacc_input.time = time;
linacc_input.signals.values = linacc-mean(linacc);
gravx_input.time = time;
gravx_input.signals.values = gravx-mean(gravx);
gravy_input.time = time;
gravy_input.signals.values = gravy-mean(gravy);
gravz_input.time = time;
gravz_input.signals.values = gravz-mean(gravz);
div_input.time = time;
div_input.signals.values = angle./linacc - mean(angle./linacc);
linvel1_input.time = time;
linvel1_input.signals.values = linvel1;
linvel2_input.time = time;
linvel2_input.signals.values = linvel2;

simout = sim('data_filtering.slx');

filt_ang = simout.angle_output.signals.values;
filt_ang_time = simout.angle_output.time - 0.65;
filt_linacc = simout.linacc_output.signals.values;
filt_linacc_time = simout.linacc_output.time - 0.2;
filt_gravx = simout.gravx_output.signals.values;
filt_gravx_time = simout.gravx_output.time - 0.15;
filt_gravy = simout.gravy_output.signals.values;
filt_gravy_time = simout.gravy_output.time - 0.25;
filt_gravz = simout.gravz_output.signals.values;
filt_gravz_time = simout.gravz_output.time - 0.2;
filt_div = simout.div_output.signals.values;
filt_div_time = simout.div_output.time - 1.5;
filt_linvel = simout.linvel1_output.signals.values;
filt_linvel_time = simout.linvel1_output.time;

figure(8)
plot(filt_ang_time, filt_ang)
hold on
plot(filt_linacc_time, filt_linacc)
legend('Angle', 'LinAcc')
xlabel('Time (s)')
ylabel('Angle (degrees)/Linear Acceleration (m/s^2)')
xlim([0, 60])

diff_filt_ang = diff(filt_ang);
adj_linacc = (-1*min(filt_linacc)+filt_linacc);
mult = adj_linacc(201:end-800) .* (10.*diff_filt_ang(201:end-799));

figure(9)
plot(filt_ang_time(651:end-350), mult)

numLevels = 8;
% perform maximal overlap discrete wavelet transform (MODWT)
wt = modwt(mult, 'db10', numLevels);

signal = transpose(-1*wt(10-1,:));
sig_time = filt_ang_time(651:end-350);

figure(2)
plot(sig_time, signal)
xlabel('Time (s)')
ylabel('Amplitude')
title('New Signal after Wavelet Transformation')

% T = mean(diff(sig_time));
% Fs = 1/T;
% L = length(sig_time);
% f = Fs*(0:(L-1))/L;
% 
% signal_fft = abs(fft(signal));
% 
% figure(3)
% plot(f, signal_fft)
% xlim([0,10])

signal_input.time = sig_time;
signal_input.signals.values = signal;

[pks2, loc2, w2, prom2] = findpeaks(signal, sig_time, 'MinPeakProminence', 0.5);
prom = min(mean(prom2), median(prom2));
pks = min(mean(pks2), median(pks2));
[pks1, loc1] = findpeaks(signal, sig_time, 'MinPeakProminence', prom, 'MinPeakHeight', pks);
pks3 = [];
loc3 = [];
for i=1:length(loc2)
    if ~ismember(loc2(i), loc1)
        pks3(end+1) = pks2(i);
        loc3(end+1) = loc2(i);
    end
end
loc4 = loc3;
loc1 = loc1;

figure(4)
plot(sig_time,signal)
hold on
plot(loc1, pks1, 'rx')
plot(loc3, pks3, 'mx')

figure(5)
plot(time, angle, 'k')
hold on
for i=transpose(loc1)
    xline(i, 'Color', 'r', 'LineWidth', 1);
end
for i=loc4
    xline(i, 'Color', 'b', 'LineWidth', 1);
end
xlabel('Time (s)')
ylabel('Angle (degrees)')

% figure(6)
% plot(time, gravy, 'k')
% hold on
% for i=transpose(loc1)
%     xline(i, 'Color', 'r', 'LineWidth', 1);
% end
% for i=loc4
%     xline(i, 'Color', 'b', 'LineWidth', 1);
% end
% plot(time, angle, 'm')