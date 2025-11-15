# PROYECTO FINAL
# VIDEOJUEGO: ADVENTURE RPG

# APUNTES
Las clases tendrán encabezado y archivo cpp.

# Para compilar en el launcher hay que indicar todos los archivos .cpp:
g++ -o Launcher/Launcher.exe Launcher/Launcher.cpp Source/GameController.cpp

# Para compilar con SFML:
Libraries/mingw64/bin/g++.exe -g -std=c++17 Launcher/Launcher.cpp Source/GameController.cpp Source/GameStates/MainMenuState.cpp Source/GameStates/GameMenuState.cpp Source/Dialog/Dialog.cpp Source/Dialog/DialogManager.cpp Source/UI/DialogBox.cpp Source/UI/MainMenuUI.cpp Source/UI/GameMenuUI.cpp -I Libraries/SFML-3.0.2/include -I Source -L Libraries/SFML-3.0.2/lib -o Launcher/Launcher.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lgdi32 -lopengl32


# Para ejecutar el Launcher.exe:
.\Launcher/Launcher.exe
o tambien:
.\Launcher/game.exe