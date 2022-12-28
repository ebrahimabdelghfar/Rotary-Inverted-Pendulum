def = legacy_code('initialize');
def.SFunctionName   = 'enc_sfun';
def.SampleTime      = 0.05;

def.OutputFcnSpec   = 'int16 y1 = NO_OP(int16 p1)';
def.StartFcnSpec    = 'void NO_OP(int16 p1, int16 p2, int16 p3)';
legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def, '-DNO_OP=0;//')

def.SourceFiles     = {fullfile(pwd,'..','src','encoder_arduino.cpp')};
def.HeaderFiles     = {'encoder_arduino.h'};
def.IncPaths        = {fullfile(pwd,'..','src')};
def.OutputFcnSpec   = 'int16 y1 = enc_output(int16 p1)';
def.StartFcnSpec    = 'void enc_init(int16 p1, int16 p2, int16 p3)';
legacy_code('sfcn_cmex_generate', def);
legacy_code('sfcn_tlc_generate', def);
legacy_code('rtwmakecfg_generate',def);

%  legacy_code('slblock_generate',def);