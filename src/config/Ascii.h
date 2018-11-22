// Copyright (c) 2018, The TurtleCoin Developers
// Copyright (c) 2018, The SmutCoin Project
//
// Please see the included LICENSE file for more information

#pragma once

const std::string windowsAsciiArt =
      
"\n                                                                   \n"
 "_______  __   __  __   __  _______  _______  _______  ___   __    _ \n"
"|       ||  |_|  ||  | |  ||       ||       ||       ||   | |  |  | |\n"
"|  _____||       ||  | |  ||_     _||       ||   _   ||   | |   |_| |\n"
"| |_____ |       ||  |_|  |  |   |  |       ||  | |  ||   | |       |\n"
"|_____  ||       ||       |  |   |  |      _||  |_|  ||   | |  _    |\n"
 "_____| || ||_|| ||       |  |   |  |     |_ |       ||   | | | |   |\n"
"|_______||_|   |_||_______|  |___|  |_______||_______||___| |_|  |__|\n"

;

const std::string nonWindowsAsciiArt = 
"\n                                                                                                       \n"
 "▄▄▄▄▄▄▄▄▄▄▄  ▄▄       ▄▄  ▄         ▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄        ▄ \n"
"▐░░░░░░░░░░░▌▐░░▌     ▐░░▌▐░▌       ▐░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░▌      ▐░▌\n"
"▐░█▀▀▀▀▀▀▀▀▀ ▐░▌░▌   ▐░▐░▌▐░▌       ▐░▌ ▀▀▀▀█░█▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀█░▌ ▀▀▀▀█░█▀▀▀▀ ▐░▌░▌     ▐░▌\n"
"▐░▌          ▐░▌▐░▌ ▐░▌▐░▌▐░▌       ▐░▌     ▐░▌     ▐░▌          ▐░▌       ▐░▌     ▐░▌     ▐░▌▐░▌    ▐░▌\n"
"▐░█▄▄▄▄▄▄▄▄▄ ▐░▌ ▐░▐░▌ ▐░▌▐░▌       ▐░▌     ▐░▌     ▐░▌          ▐░▌       ▐░▌     ▐░▌     ▐░▌ ▐░▌   ▐░▌\n"
"▐░░░░░░░░░░░▌▐░▌  ▐░▌  ▐░▌▐░▌       ▐░▌     ▐░▌     ▐░▌          ▐░▌       ▐░▌     ▐░▌     ▐░▌  ▐░▌  ▐░▌\n"
 "▀▀▀▀▀▀▀▀▀█░▌▐░▌   ▀   ▐░▌▐░▌       ▐░▌     ▐░▌     ▐░▌          ▐░▌       ▐░▌     ▐░▌     ▐░▌   ▐░▌ ▐░▌\n"
  "        ▐░▌▐░▌       ▐░▌▐░▌       ▐░▌     ▐░▌     ▐░▌          ▐░▌       ▐░▌     ▐░▌     ▐░▌    ▐░▌▐░▌\n"
 "▄▄▄▄▄▄▄▄▄█░▌▐░▌       ▐░▌▐░█▄▄▄▄▄▄▄█░▌     ▐░▌     ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄█░▌ ▄▄▄▄█░█▄▄▄▄ ▐░▌     ▐░▐░▌\n"
"▐░░░░░░░░░░░▌▐░▌       ▐░▌▐░░░░░░░░░░░▌     ▐░▌     ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░▌      ▐░░▌\n"
" ▀▀▀▀▀▀▀▀▀▀▀  ▀         ▀  ▀▀▀▀▀▀▀▀▀▀▀       ▀       ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀        ▀▀ \n";

/* Windows has some characters it won't display in a terminal. If your ascii
   art works fine on Windows and Linux terminals, just replace 'asciiArt' with
   the art itself, and remove these two #ifdefs and above ascii arts */
#ifdef _WIN32
const std::string asciiArt = windowsAsciiArt;
#else
const std::string asciiArt = nonWindowsAsciiArt;
#endif
