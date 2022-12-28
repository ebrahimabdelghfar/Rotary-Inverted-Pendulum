def = legacy_code('initialize');
def.SFunctionName = 'aout_sfun';

def.OutputFcnSpec = 'void NO_OP(uint8 p1, uint8 u1)';
def.StartFcnSpec  = 'void NO_OP(uint8 p1)';
legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def, '-DNO_OP=//') 

def.SourceFiles   = {fullfile(pwd,'..','src','aout_arduino.cpp')};
def.HeaderFiles   = {'aout_arduino.h'};
def.IncPaths      = {fullfile(pwd,'..','src')};
def.OutputFcnSpec = 'void aout_output(uint8 p1, uint8 u1)';
def.StartFcnSpec  = 'void aout_init(uint8 p1)';
legacy_code('sfcn_cmex_generate', def);
legacy_code('sfcn_tlc_generate', def);
legacy_code('rtwmakecfg_generate',def);

%  legacy_code('slblock_generate',def);