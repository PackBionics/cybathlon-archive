% clc
% close all

t = readtable('CondensedDataMedium.csv');

time = table2array(t(:, 'Time'));
angle = table2array(t(:, 'Angle'));
linacc = table2array(t(:, 'LinAcc'));
gravx = table2array(t(:, 'GravX'));
gravy = table2array(t(:, 'GravY'));
gravz = table2array(t(:, 'GravZ'));
linvel1 = table2array(t(:, 'LinVel1'));
linvel2 = table2array(t(:, 'LinVel2'));

figure(1)
plot(time, linacc)

figure(2)
plot(time, angle./linacc)

figure(3)
plot(time, angle)
hold on
plot(time, linacc)
plot(time, gravx)
plot(time, gravy)
plot(time, gravz)
legend('Angle', 'LinAcc', 'GravX', 'GravY', 'GravZ')

%% FFTs

T = mean(diff(time));
Fs = 1/T;
L = length(time);
f = Fs*(0:(L-1))/L;

ang_fft = abs(fft(angle));
linacc_fft = abs(fft(linacc));
gravx_fft = abs(fft(gravx));
gravy_fft = abs(fft(gravy));
gravz_fft = abs(fft(gravz));
div_fft = abs(fft(angle./linacc));
linvel1_fft = abs(fft(linvel1));
linvel2_fft = abs(fft(linvel2));


figure(1)
semilogy(f, ang_fft)
xlim([0,20])

figure(2)
semilogy(f, linacc_fft)
xlim([0,20])

figure(3)
semilogy(f, gravx_fft)
xlim([0,20])

figure(4)
semilogy(f, gravy_fft)
xlim([0,20])

figure(5)
semilogy(f, gravz_fft)
xlim([0,20])

figure(6)
semilogy(f, div_fft)
xlim([0,20])

figure(7)
plot(f, linvel1_fft)
xlim([0,20])

figure(8)
plot(f, linvel2_fft)
xlim([0,20])

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


%%  Save filtered signals to 
filt_ang = out.angle_output.signals.values;
filt_ang_time = out.angle_output.time - 0.65;
filt_linacc = out.linacc_output.signals.values;
filt_linacc_time = out.linacc_output.time - 0.2;
filt_gravx = out.gravx_output.signals.values;
filt_gravx_time = out.gravx_output.time - 0.15;
filt_gravy = out.gravy_output.signals.values;
filt_gravy_time = out.gravy_output.time - 0.25;
filt_gravz = out.gravz_output.signals.values;
filt_gravz_time = out.gravz_output.time - 0.2;
filt_div = out.div_output.signals.values;
filt_div_time = out.div_output.time - 1.5;
filt_linvel = out.linvel1_output.signals.values;
filt_linvel_time = out.linvel1_output.time;


figure(1)
plot(filt_ang_time, filt_ang)
hold on
% plot(filt_gravx_time, filt_gravx)
adj_linacc = -1*min(filt_linacc)+filt_linacc;
plot(filt_ang_time(2:end), 100.*diff(filt_ang))
plot(filt_linacc_time, adj_linacc)
plot(filt_gravy_time, filt_gravy)

diff_filt_ang = diff(filt_ang);
mult = adj_linacc(201:end-800) .* (10.*diff_filt_ang(201:end-799));
plot(filt_ang_time(651:end-350), mult)
legend('Angle', 'Diff Angle', 'LinAcc', 'GravY', 'Mult')


% plot(time, angle)
% hold on
% plot(filt_linvel_time, filt_linvel)

% figure(2)
% plot(cumtrapz(test))

%%
figure(1)
findpeaks(filt_ang, filt_ang_time, 'MinPeakDistance', 0.3)
% hold on
% findpeaks(smooth(diff(filt_ang, 2)), filt_ang_time(3:end), 'MinPeakDistance', 0.4)

figure(2)
findpeaks(filt_linacc, filt_linacc_time, 'MinPeakDistance', 0.1, 'MinPeakProminence', 0.5)
figure(3)
findpeaks(filt_gravx, filt_gravx_time, 'MinPeakDistance', 0.3, 'MinPeakProminence', 1)
figure(4)
findpeaks(filt_gravy, filt_gravy_time, 'MinPeakDistance', 0.3, 'MinPeakProminence', 1)
figure(5)
findpeaks(filt_gravz, filt_gravz_time, 'MinPeakDistance', 0.3, 'MinPeakProminence', 1)

figure(6)
hold on
findpeaks(filt_ang, filt_ang_time, 'MinPeakDistance', 0.3)
findpeaks(filt_linacc, filt_linacc_time, 'MinPeakDistance', 0.1, 'MinPeakProminence', 0.5)
findpeaks(filt_gravx, filt_gravx_time, 'MinPeakDistance', 0.3, 'MinPeakProminence', 1)
findpeaks(filt_gravy, filt_gravy_time, 'MinPeakDistance', 0.3, 'MinPeakProminence', 1)
findpeaks(filt_gravz, filt_gravz_time, 'MinPeakDistance', 0.3, 'MinPeakProminence', 1)

legend('', 'Angle', '', 'Linear Acc', '', 'Grav X', '', 'Grav Y', '', 'Grav Z')


%% Wavelets

% test = angle./linacc - mean(angle./linacc);
test = mult;
% test = filt_ang(10000:end)./filt_linvel(10000:end);
% test = filt_ang(10000:end)./filt_linvel(10000:end);
% for i=1:length(test)
%     if test(i) > 30
%         test(i) = 30;
%     elseif test(i) < -30
%         test(i) = -30;
%     end
% end

% define number of levels to use
numLevels = 8;
% perform maximal overlap discrete wavelet transform (MODWT)
wt = modwt(test, 'db3', numLevels);
% COMPARE COEFFICENTS FOR ALL MODWT SCALES

% get number of Wavelet Scales
[numScales, ~] = size(wt);

% create figure
fig = figure(1);
fig.Units = 'normalized';
fig.Position = [0 0 1 1];

% plot original signal
subplot(numScales+1,1,1)
plot(test, 'r-')
title('Orginal Signal', 'FontSize', 14)
axis tight

% plot wavelet scale coefficents
for i=2:numScales+1
    
    subplot(numScales+1,1,i)
    plot(wt(i-1,:))
    title(strcat('Wavelet Scale 2^', string(i-2)), 'FontSize', 14)
    axis tight
end

xlabel('Time', 'FontSize', 14)

%% 
% create figure
fig = figure(2);
fig.Units = 'normalized';
fig.Position = [0 0 1 1];

% initialize an array to store the coefficents corresponding to scale 2^4
recwt = zeros(size(wt));

% store coefficents corresponding to scale 4 in array
recwt(4,:) = wt(4,:);

% reconstruct signal using only scale 4 with inverse transform
recECG = imodwt(recwt,'db3');

% compare original signal and reconstructed
% plot original signal
subplot(2,1,1)
plot(filt_ang_time(651:end-350), mult, 'r-')
title('Orginal ECG', 'FontSize', 16)
xlabel('Time', 'FontSize', 14)
axis tight
% plot reconstructed signal
subplot(2,1,2)
plot(filt_ang_time(651:end-350), wt(10-1,:))
hold on
plot(filt_ang_time, filt_ang)
plot(filt_linacc_time, filt_linacc)
title('Reconstructed ECG', 'FontSize', 16)
xlabel('Time', 'FontSize', 14)
axis tight

%% final signal
signal = transpose(-1*wt(10-1,:));
sig_time = filt_ang_time(651:end-350);

figure(1)
plot(sig_time, signal)

T = mean(diff(sig_time));
Fs = 1/T;
L = length(sig_time);
f = Fs*(0:(L-1))/L;

signal_fft = abs(fft(signal));

figure(2)
plot(f, signal_fft)
xlim([0,10])

signal_input.time = sig_time;
signal_input.signals.values = signal;

[pks1, loc1] = findpeaks(signal, sig_time, 'MinPeakProminence', 11, 'MinPeakHeight', mean(pks2));
[pks2, loc2] = findpeaks(signal, sig_time, 'MinPeakProminence', 0.5);
pks3 = [];
loc3 = [];
for i=1:length(loc2)
    if ~ismember(loc2(i), loc1)
        pks3(end+1) = pks2(i);
        loc3(end+1) = loc2(i);
    end
end
loc4 = loc3 + 0.2;

figure(3)
plot(sig_time,signal)
hold on
plot(loc1, pks1, 'rx')
plot(loc3, pks3, 'mx')

figure(4)
plot(time, angle, 'k')
hold on
for i=transpose(loc1)
    xline(i, 'Color', 'r', 'LineWidth', 1);
end
for i=loc4
    xline(i, 'Color', 'b', 'LineWidth', 1);
end

figure(5)
plot(time, gravy, 'k')
hold on
for i=transpose(loc1)
    xline(i, 'Color', 'r', 'LineWidth', 1);
end
for i=loc4
    xline(i, 'Color', 'b', 'LineWidth', 1);
end
plot(time, angle, 'm')
