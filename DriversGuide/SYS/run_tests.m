function run_tests(hardwareName)

if ~iscell(hardwareName)
    hardwareName = {hardwareName};
end

% Raspberry Pi
if ismember('raspi', hardwareName)
    r = raspberrypi;
    models = {'digitalio_raspi_test','encoder_raspi_test','analog_output_raspi_test'};
    for k = 1:numel(models)
        load_system(models{k});
        mode = get_param(models{k}, 'SimulationMode');
        if ~isequal(mode,'normal')
            set_param(models{k},'SimulationMode','normal');
            c = onCleanup(@() set_param(models{k},'SimulationMode',mode));
        end
        sim(models{k},1);
        buildModel(models{k});
        stop(r,models{k});
        close_system(models{k},0);
    end
end

% Arduino
if ismember(hardwareName, 'arduino')
    models = {'digitalio_arduino_test','analog_output_arduino_test','encoder_arduino_test'};
    for k = 1:numel(models)
        load_system(models{k});
        sim(models{k},1);
        buildModel(models{k});
        close_system(models{k},0);
    end
end
end

function buildModel(model)
open_system(model);
rtwbuild(model);
end

% Arduino
