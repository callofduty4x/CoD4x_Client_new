@echo off
mingw32-make DEBUG=true snd_driver=soloud -j8 
if errorlevel==0 (
	xcopy bin\cod4x_game.exe "D:\SteamLibrary\steamapps\common\Call of Duty 4" /Y
	cd "D:\SteamLibrary\steamapps\common\Call of Duty 4"
	D:
	cod4x_game.exe
)
