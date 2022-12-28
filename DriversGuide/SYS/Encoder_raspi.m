classdef Encoder_raspi < realtime.internal.SourceSampleTime ...
        & coder.ExternalDependency ...
        & matlab.system.mixin.Propagates ...
        & matlab.system.mixin.CustomIcon 
    %
    %Read the position of a quadrature encoder.
    %
    %
    
    % Copyright 2014 The MathWorks, Inc.
    %#codegen
    %#ok<*EMCA>
    
    properties (Nontunable)
        Encoder = 0
        PinA = 4
        PinB = 14
    end
    
    properties (Constant, Hidden)
        AvailablePin = [4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27];
        MaxNumEncoder = 3
    end
    
    methods
        % Constructor
        function obj = Encoder_raspi(varargin)
            coder.allowpcode('plain');
            
            % Support name-value pair arguments when constructing the object.
            setProperties(obj,nargin,varargin{:});
        end
        
        function set.PinA(obj,value)
            coder.extrinsic('sprintf') % Do not generate code for sprintf
            validateattributes(value,...
                {'numeric'},...
                {'real','nonnegative','integer','scalar'},...
                '', ...
                'PinA');
            assert(any(value == obj.AvailablePin), ...
                'Invalid value for Pin. Pin must be one of the following: %s', ...
                sprintf('%d ', obj.AvailablePin));
            obj.PinA = value;
        end
        
        function set.PinB(obj,value)
            coder.extrinsic('sprintf') % Do not generate code for sprintf
            validateattributes(value,...
                {'numeric'},...
                {'real','nonnegative','integer','scalar'},...
                '', ...
                'PinB');
            assert(any(value == obj.AvailablePin), ...
                'Invalid value for Pin. Pin must be one of the following: %s', ...
                sprintf('%d ', obj.AvailablePin));
            obj.PinB = value;
        end
        
        function set.Encoder(obj,value)
            validateattributes(value,...
                {'numeric'},...
                {'real','nonnegative','integer','scalar','>=',0,'<=',obj.MaxNumEncoder},...
                '', ...
                'Encoder');
            obj.Encoder = value;
        end
    end
    
    methods (Access=protected)
        function setupImpl(obj)
            if coder.target('Rtw')
                % Call: void encoderInit(uint8_T num, uint8_T pinA, uint8_T pinB)
                coder.cinclude('encoder_raspi.h');
                coder.ceval('encoderInit', obj.Encoder, obj.PinA, obj.PinB);
            end
        end
        
        function y = stepImpl(obj)
            y = int32(0);
            if coder.target('Rtw')
                % Call: int32_T encoderOutput(uint8_T num)
                y = coder.ceval('encoderOutput', obj.Encoder);
            end
        end
        
        function releaseImpl(obj)
            if coder.target('Rtw')
                % Call: void encoderTerminate(uint8_T num)
                coder.ceval('encoderTerminate', obj.Encoder);
            end
        end
    end
    
    methods (Access=protected)
        %% Define output properties
        function num = getNumInputsImpl(~)
            num = 0;
        end
        
        function num = getNumOutputsImpl(~)
            num = 1;
        end
        
        function flag = isOutputSizeLockedImpl(~,~)
            flag = true;
        end
        
        function varargout = isOutputFixedSizeImpl(~,~)
            varargout{1} = true;
        end
        
        function flag = isOutputComplexityLockedImpl(~,~)
            flag = true;
        end
        
        function varargout = isOutputComplexImpl(~)
            varargout{1} = false;
        end
        
        function varargout = getOutputSizeImpl(~)
            varargout{1} = [1,1];
        end
        
        function varargout = getOutputDataTypeImpl(~)
            varargout{1} = 'int32';
        end
        
        function icon = getIconImpl(~)
            % Define a string as the icon for the System block in Simulink.
            icon = 'Encoder';
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
            name = 'Encoder';
        end
        
        function b = isSupportedContext(context)
            b = context.isCodeGenTarget('rtw');
        end
        
        function updateBuildInfo(buildInfo, context)
            if context.isCodeGenTarget('rtw')
                % Update buildInfo
                rootDir = fullfile(fileparts(mfilename('fullpath')),'..','src');
                buildInfo.addIncludePaths(rootDir);
                buildInfo.addIncludeFiles('encoder_raspi.h');
                buildInfo.addSourceFiles('encoder_raspi.c', rootDir);
                buildInfo.addLinkFlags({'-lwiringPi'});
            end
        end
    end
end
