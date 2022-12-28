classdef AnalogOutput_raspi < matlab.System ...
        & coder.ExternalDependency ...
        & matlab.system.mixin.Propagates ...
        % ServoBlaster ServoBlaster system object
    %Output an analog voltage using ServoBlaster PWM driver. 
    %
    % Pin must be one of the following: 4, 17, 18, 27, 22, 23, 24, 25.
    % Input port expects a numeric scalar between 0 and 100 with 0
    % corresponding to 0 Volt and 100 corresponding to Vdd (+3.3 Volt on
    % Raspberry Pi). Values outside this range is saturated to 0 or 100.
    % 
    % In order to use this driver, you need to install ServoBlaster. First,
    % open an SSH terminal to your Raspberry Pi:
    % 
    % >> r = raspberrypi;
    % >> openShell(r, 'ssh')
    % 
    % The openShell command launches a PuTTY SSH terminal. Login to your
    % Raspberry Pi and execute the following commands to install
    % ServoBlaster:
    % 
    % # sudo apt-get -y install git-core
    % # git clone https://github.com/richardghirst/PiBits.git
    % # cd PiBits/ServoBlaster/user
    % # make 
    % # sudo ./servod
    %
    
    % Copyright 2014-2015 The MathWorks, Inc.
    %#codegen
    %#ok<*EMCA>
    
    properties (Nontunable)
        Pin = 4
    end
    
    properties (Constant, Hidden)
        AvailablePin     = [4 17 18 27 22 23 24 25];
        AvailableChannel = [0 1  2  3  4  5  6  7];
    end
    
    properties (Dependent, Access = private)
        Channel
    end
    
    methods
        % Constructor
        function obj = AnalogOutput_raspi(varargin)
            coder.allowpcode('plain');
            
            % Support name-value pair arguments when constructing the object.
            setProperties(obj,nargin,varargin{:});
        end
        
        function set.Pin(obj,value)
            % Check that the Pin number is one of those supported by
            % ServoBlaster
            coder.extrinsic('sprintf') % Do not generate code for sprintf
            validateattributes(value,...
                {'numeric'},...
                {'real','nonnegative','integer','scalar'},...
                '', ...
                'Pin');
            assert(any(value == obj.AvailablePin), ...
                'Invalid value for Pin. Available Pins are: %s', ...
                sprintf('%d ', obj.AvailablePin));
            obj.Pin = value;
        end
        
        function ret = get.Channel(obj)
            % Convert Pin number to a ServoBlaster channel number
            ret = obj.AvailableChannel(obj.Pin == obj.AvailablePin);
        end
    end

    methods (Access = protected)
        %% Common functions
        function setupImpl(obj) %#ok<MANU>
            if coder.target('Rtw')
                coder.cinclude('servoblaster.h');
                % No initialization is needed. The driver should already be
                % active at this point
            end
        end
        
        function stepImpl(obj,u)
            if coder.target('Rtw')
                coder.ceval('writeServoBlaster', obj.Channel, int32(u));
            end
        end
        
        function resetImpl(obj) %#ok<MANU>
            % Initialize discrete-state properties.
        end
    end
    
    methods (Access=protected)
        %% Define input properties
        function num = getNumInputsImpl(~)
            num = 1;
        end
        
        function num = getNumOutputsImpl(~)
            num = 0;
        end

        function flag = isInputSizeLockedImpl(~,~)
            flag = true;
        end
        
        function varargout = isInputFixedSizeImpl(~,~)
            varargout{1} = true;
        end
        
        function flag = isInputComplexityLockedImpl(~,~)
            flag = true;
        end
        
        function varargout = isInputComplexImpl(~)
            varargout{1} = false;
        end
        
        function validateInputsImpl(~, u)
            if isempty(coder.target)
                % Run input validation only in Simulation
                validateattributes(u,{'double','single','int32',...
                    'uint32','int16','uint16','int8','uint8'},...
                    {'scalar','>=',0,'<=',100},'','u'); 
            end
        end
        
        function icon = getIconImpl(~)
            % Define a string as the icon for the System block in Simulink.
            icon = 'Sink';
        end
    end
    
    methods (Static, Access=protected)
        function simMode = getSimulateUsingImpl(~)
            simMode = 'Interpreted execution';
        end
        
        function isVisible = showSimulateUsingImpl
            isVisible = false;
        end
    end
    
    methods (Static)
        function name = getDescriptiveName()
            name = 'Analog Output';
        end
        
        function b = isSupportedContext(context)
            b = context.isCodeGenTarget('rtw');
        end
        
        function updateBuildInfo(buildInfo, context)
            if context.isCodeGenTarget('rtw')
                % Update buildInfo
                rootDir = fullfile(fileparts(mfilename('fullpath')),'..','src');
                buildInfo.addIncludePaths(rootDir);
                buildInfo.addIncludeFiles('servoblaster.h');
                buildInfo.addSourceFiles('servoblaster.c',rootDir);
            end
        end
    end
end
