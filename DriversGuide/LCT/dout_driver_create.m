def = legacy_code('initialize');
def.SFunctionName  = 'dout_sfun';

def.OutputFcnSpec  = 'void NO_OP(uint8 p1, boolean u1)';
def.StartFcnSpec   = 'void NO_OP(uint8 p1)';
legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def, '-DNO_OP=//') 

def.SourceFiles     = {fullfile(pwd,'..','src','digitalio_arduino.cpp')};
def.HeaderFiles     = {'digitalio_arduino.h'};
def.IncPaths        = {fullfile(pwd,'..','src')};
def.OutputFcnSpec  = 'void writeDigitalPin(uint8 p1, boolean u1)';
def.StartFcnSpec   = 'void DOUT_INIT(uint8 p1)';
legacy_code('sfcn_cmex_generate', def);
legacy_code('sfcn_tlc_generate', def);
legacy_code('rtwmakecfg_generate',def);

%   legacy_code('slblock_generate',def);