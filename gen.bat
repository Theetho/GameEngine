@echo off
echo Deleting GameEngine.sln... 
del GameEngine.sln 
echo Deleting Engine\Engine.vcxproj... 
del Engine\Engine.vcxproj
echo Deleting Game\Game.vcxproj...
del Game\Game.vcxproj
echo Deleting Sandbox\Sandbox.vcxproj...
del Sandbox\Sandbox.vcxproj
echo Deleting 2DDevelop\2DDevelop.vcxproj...
del 2DDevelop\2DDevelop.vcxproj
call vendor\premake\premake5.exe vs2019