<p align="center">
	<a href="https://github.com/wy3/luacef">
		<img src="https://github.com/wy3/luacef/raw/master/lcf.png" alt="" width="215px">
	</a>
	<h1 align="center"> LuaCEF </h1>
	<p align="center">
    	<strong> Chromium Embedded Framework for Lua. </strong>
 	</p>
</p>

## --- __todo__ [60%]

### Base on:
- [Lua 5.3.4](https://www.lua.org/ftp/)
- [CEF 3.3112 - Chromium 60](http://opensource.spotify.com/cefbuilds/index.html)

### OS supported
- [x] Windows
- [ ] Linux (todo)
- [ ] ~~Mac OSX~~

### Build
#### For Windows:
- Run __build_win.lua__
- Add all resources files in __Release__ and __Resources__ folder (from __CEF__ distribution you can [download here](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows32_minimal.tar.bz2) for current version).

....

### How to store pointer?

```erlang
 lua:newuserdata  <- alloc [4-byte]
~~~~~~~~~~~~~~~~
       |
       v
    <ptr**> -> <ptr*> = <udata*> <- alloc [n-byte]
       |                   |---> ::free
       v                   |---> ::set, get
    <self**>  <------------|      ~~~~~~~~
    ~~~~~~~~                          ^
       |                               \
       v                             ~~~~~~~~~
[method, property] <- <metatable> -> reference
       |
       v
     return

  __LUA_side__
```

#### Simple example

```lua
cef = require("luacef")

-- new main args, app
local args, app = cef.newMainArgs(), cef.newApp() 

-- execute process and check, not necessary
local code = cef.ExecuteProcess(args, app)
if (code >= 0) then os.exit() end

-- print version
cef.printversion()

-- new cef settings
local settings = cef.newSettings {

	log_severity = 99;	-- disable debug log and log file		
	single_process = 1; -- must set single-process for Lua command line	
}

-- enable high DPI support, for windows 7 or newer
cef.EnableHighDPISupport()

-- initialize application
code = cef.Initialize(args, settings, app)
if (code == 0) then os.exit() end

-- create window info
local window_info = cef.newWindowInfo {

	-- set window name
	window_name = "Hello World!"; -- Lua string be convert to cef string, accept unicode
}

-- create browser settings for create browser
local browser_settings = cef.newBrowserSettings()

-- create life span handler
local life_span = cef.newLifeSpanHandler {

	-- implement OnAfterCreated callback function
	OnAfterCreated = function(self, browser) -- event
		print("-- on after created --")
		print(self, browser) --> LifeSpanHandler: <address>, Browser: <address>
		print('Window handle: ', browser:GetHost():GetWindowHandle())

		-- show browser window
		cef.ShowBrowser(browser, 10)
	end;
}

-- implement OnBeforeClose with other way
function life_span:OnBeforeClose(browser)
	print("-- on before close --")

	-- test browser's method
	print('can go back:', browser:CanGoBack())
	print('can go forward:', browser:CanGoForward())

	-- quit cef messgae loop
	cef.QuitMessageLoop()
end;

-- keyboard handler
keyboard = cef.newKeyboardHandler {
	-- pre-key event
	OnPreKeyEvent = function(self, browser, event, os_event, is_keyboard_shortcut)

		if event.type == 2 then -- test release key
			if event.windows_key_code == 0xd then
				print('Enter key released')
			elseif event.windows_key_code == 0x1b then
				print('ESC key released')
			end
		end
		return 0
	end;
}

-- new client
local client = cef.newClient {
	-- set life span handler by return it
	GetLifeSpanHandler = function(self) 
		return life_span
	end;
	-- set keyboard handler
	GetKeyboardHandler = function(self)
		return keyboard
	end;
}

-- url string
local url = 'https://www.google.com/'

-- create browser window
cef.CreateBrowser(window_info, client, url, browser_settings, nil)

-- run message loop
-- in cef settings, if multi_threaded_message_loop is true (1), must use window message loop
cef.RunMessageLoop()

-- shutdown
cef.Shutdown()

-- release callback/handler object, it has no __gc
client:release()
app:release()
life_span:release()
keyboard:release()
```

<p align="center">
<img src="https://i.imgur.com/8mmTqjW.png" width="600">
</p>

### License [Apache 2.0](https://github.com/wy3/luacef/blob/master/LICENSE)

Copyright © 2018 by [__me__](https://github.com/wy3).

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at [here](http://www.apache.org/licenses/LICENSE-2.0).
   
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
