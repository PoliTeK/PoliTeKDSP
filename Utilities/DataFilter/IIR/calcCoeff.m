%% Codice Matlab per Export C++ IIR (Bessel & Butterworth 2nd/4th Order)
clc
clear

fs = 60 ;           % Frequenza di campionamento
fc_bes = 5;         % Cutoff Bessel
fc_but = 5;         % Cutoff Butterworth

% --- CALCOLO COEFFICIENTI ---
[b_but2, a_but2] = butter(2, fc_but/(fs/2), 'low');
[b_but4, a_but4] = butter(4, fc_but/(fs/2), 'low');

[b_bes_s2, a_bes_s2] = besself(2, 2*pi*fc_bes);
[b_bes2, a_bes2] = bilinear(b_bes_s2, a_bes_s2, fs);

[b_bes_s4, a_bes_s4] = besself(4, 2*pi*fc_bes);
[b_bes4, a_bes4] = bilinear(b_bes_s4, a_bes_s4, fs);

% --- GENERAZIONE OUTPUT C++ ---
fprintf('/* Copia questo blocco nella sezione private di iir.h */\n\n');

% --- Butterworth 2nd ---
print_block('Butterworth', 2, 'Butter', 'butter', b_but2, a_but2);

% --- Butterworth 4th ---
print_block('Butterworth', 4, 'Butter4', 'butter4', b_but4, a_but4);

% --- Bessel 2nd ---
print_block('Bessel', 2, 'Bessel', 'bessel', b_bes2, a_bes2);

% --- Bessel 4th ---
print_block('Bessel', 4, 'Bessel4', 'bessel4', b_bes4, a_bes4);

%% Funzione di formattazione specifica
function print_block(label, N, buffName, varName, b, a)
    fprintf('    // --- %s %dnd Order ---\n', label, N);
    fprintf('    static const int _%sORDER = %d;\n', buffName, N);
    
    % Numeratore b
    fprintf('    float _%s_b[_%sORDER + 1] = {', varName, buffName);
    for i = 1:length(b)-1
        fprintf('%.8ff, ', b(i));
    end
    fprintf('%.8ff};\n', b(end));
    
    % Denominatore a
    fprintf('    float _%s_a[_%sORDER + 1] = {', varName, buffName);
    for i = 1:length(a)-1
        fprintf('%.8ff, ', a(i));
    end
    fprintf('%.8ff};\n', a(end));
    
    % Buffer (sempre inizializzato a 0.0f)
    buffList = repmat({'0.0f'}, 1, N);
    buffStr = strjoin(buffList, ', ');
    fprintf('    float _%s_buff[_%sORDER] = {%s};\n\n', buffName, buffName, buffStr);
end