def = legacy_code('initialize');
def.SFunctionName   = 'din_sfun';
def.SampleTime      = 0.05;

def.OutputFcnSpec   = 'boolean y1 = NO_OP(uint8 p1)';
def.StartFcnSpec    = 'void NO_OP(uint8 p1)';
legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def, '-DNO_OP=0.0;//')

def.SourceFiles     = {fullfile(pwd,'..','src','digitalio_arduino.cpp')};
def.HeaderFiles     = {'digitalio_arduino.h'};
def.IncPaths        = {fullfile(pwd,'..','src')};
def.OutputFcnSpec   = 'boolean y1 = readDigitalPin(uint8 p1)';
def.StartFcnSpec    = 'void DIN_INIT(uint8 p1)';
legacy_code('sfcn_cmex_generate', def);
legacy_code('sfcn_tlc_generate', def);
legacy_code('rtwmakecfg_generate',def);

%  legacy_code('slblock_generate',def);