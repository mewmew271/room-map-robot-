clear
clc
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end
clear
clc

%User Defined Properties 
serialPort = 'COM3';            % define COM port #
plotTitle = 'Serial Data Log';  % plot title
xLabel = 'Elapsed Time (s)';    % x-axis label
yLabel = 'Data';                % y-axis label
plotGrid = 'on';                % 'off' to turn off grid
delay = .1;                    % make sure sample faster than resolution
 
%Define Function Variables
time = 0;
distance = 0;
count = 0;
 
%Set up Plot
plotGraph = plot(time,distance,'-mo',...
                'LineWidth',1,...
                'MarkerEdgeColor','k',...
                'MarkerFaceColor',[.49 1 .63],...
                'MarkerSize',2);
             
title(plotTitle,'FontSize',25);
xlabel(xLabel,'FontSize',15);
ylabel(yLabel,'FontSize',15);

grid(plotGrid);
 
%Open Serial COM Port
s = serial(serialPort);
disp('Close Plot to End Session');
fopen(s);
 

x = 0; 
dat2 = 0;

while ishandle(plotGraph) %Loop when Plot is Active
     
    dat = fscanf(s,'%f'); %Read Data from Serial as Float
    dat2 = fscanf(s,'%f'); %Read Data from Serial as Float 
   
    if(~isempty(dat) && isfloat(dat)) %Make sure Data Type is Correct        
        count = count + 1;    
               
        distance(count) = dat(1); %Extract 1st Data Element   
%         distance(count) = 500;
        angleFace(count) = dat2(1);
        possition = angleFace(count);
        angle = angleFace * 0.523599; %radions
        distance2 = distance(count);
        x(possition + 1) = round(distance2 * cos(angle(count)));
        y(possition + 1) = round(distance2 * sin(angle(count)));
    
        %Set Axis according to Scroll Width
       
        set(plotGraph,'XData',x,'YData',y); 
        pause(delay);
    end
end
 
%Close Serial COM Port and Delete useless Variables
close(s);
clear count dat delay max min plotGraph plotGrid plotTitle s ...
        scrollWidth serialPort xLabel yLabel;
 
 
disp('Session Terminated...');

