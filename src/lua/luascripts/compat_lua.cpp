#include &ltstring&gt

const std::string compat_lua = R"(
bz2.compressLimit       = bz2.COMPRESS_LIMIT
bz2.compressNomem       = bz2.COMPRESS_NOMEM
bz2.decompressBad       = bz2.DECOMPRESS_BAD
bz2.decompressEof       = bz2.DECOMPRESS_EOF
bz2.decompressLimit     = bz2.DECOMPRESS_LIMIT
bz2.decompressNomem     = bz2.DECOMPRESS_NOMEM
bz2.decompressType      = bz2.DECOMPRESS_TYPE
elem.FLAG_MOVABLE       = sim.FLAG_MOVABLE
elem.FLAG_PHOTDECO      = sim.FLAG_PHOTDECO
elem.FLAG_SKIPMOVE      = sim.FLAG_SKIPMOVE
elem.FLAG_STAGNANT      = sim.FLAG_STAGNANT
elem.PROP_BLACK         = 0
elem.PROP_DRAWONCTYPE   = 0
elem.ST_GAS             = 0
elem.ST_LIQUID          = 0
elem.ST_NONE            = 0
elem.ST_SOLID           = 0
event.aftersimdraw      = event.AFTERSIMDRAW
event.aftersim          = event.AFTERSIM
event.beforesimdraw     = event.BEFORESIMDRAW
event.beforesim         = event.BEFORESIM
event.blur              = event.BLUR
event.close             = event.CLOSE
event.getmodifiers      = event.getModifiers
event.keypress          = event.KEYPRESS
event.keyrelease        = event.KEYRELEASE
event.mousedown         = event.MOUSEDOWN
event.mousemove         = event.MOUSEMOVE
event.mouseup           = event.MOUSEUP
event.mousewheel        = event.MOUSEWHEEL
event.textediting       = event.TEXTEDITING
event.textinput         = event.TEXTINPUT
event.tick              = event.TICK
ren.colourMode          = ren.colorMode
sim.can_move            = sim.canMove
sim.decoColour          = sim.decoColor
sim.framerender         = sim.frameRender
sim.gspeed              = sim.golSpeedRatio
sim.neighbours          = sim.neighbors
sim.partNeighbours      = sim.partNeighbors
sim.randomseed          = sim.randomSeed
sim.waterEqualisation   = sim.waterEqualization
tpt.active_menu         = ui.activeMenu
tpt.display_mode        = ren.useDisplayPreset
tpt.get_clipboard       = plat.clipboardCopy
tpt.get_name            = tpt.getUserName
tpt.menu_enabled        = ui.menuEnabled
tpt.num_menus           = ui.numMenus
tpt.perfectCircleBrush  = ui.perfectCircleBrush
tpt.reset_spark         = sim.resetSpark
tpt.reset_velocity      = sim.resetVelocity
tpt.set_clipboard       = plat.clipboardPaste
tpt.setdrawcap          = tpt.drawCap
tpt.setfpscap           = tpt.fpsCap
tpt.get_numOfParts      = sim.partCount
ui.MOUSE_UP_BLUR        = ui.MOUSEUP_BLUR
ui.MOUSE_UP_DRAW_END    = ui.MOUSEUP_DRAWEND
ui.MOUSE_UP_NORMAL      = ui.MOUSEUP_NORMAL
sim.TOOL_HEAT           = tools.index.DEFAULT_TOOL_HEAT
sim.TOOL_COOL           = tools.index.DEFAULT_TOOL_COOL
sim.TOOL_VAC            = tools.index.DEFAULT_TOOL_VAC
sim.TOOL_PGRV           = tools.index.DEFAULT_TOOL_PGRV
sim.TOOL_AIR            = tools.index.DEFAULT_TOOL_AIR
sim.TOOL_NGRV           = tools.index.DEFAULT_TOOL_NGRV
sim.TOOL_MIX            = tools.index.DEFAULT_TOOL_MIX
sim.TOOL_CYCL           = tools.index.DEFAULT_TOOL_CYCL
sim.TOOL_WIND           = tools.index.DEFAULT_TOOL_WIND
if socket then
	socket.gettime = socket.getTime
end
print = tpt.log

local function fake_boolean_wrapper(func, true_is_1)
	return function(param)
		if not param then
			return func() and 1 or 0
		end
		local enable
		if true_is_1 then
			enable = param == 1
		else
			enable = param ~= 0
		end
		func(enable)
	end
end
tpt.set_console        = fake_boolean_wrapper(ui.console          , true )
tpt.ambient_heat       = fake_boolean_wrapper(sim.ambientHeatSim  , true )
tpt.heat               = fake_boolean_wrapper(sim.heatSim         , false)
tpt.set_pause          = fake_boolean_wrapper(sim.paused          , false)
tpt.decorations_enable = fake_boolean_wrapper(ren.decorations     , false)
tpt.hud                = fake_boolean_wrapper(ren.hud             , false)
tpt.newtonian_gravity  = fake_boolean_wrapper(sim.newtonianGravity, false)
ren.debugHUD           = fake_boolean_wrapper(ren.debugHud        , false)

function tpt.setdebug(flags)
	-- correct usage passed 0 to 1 arguments
	tpt.debug(flags or 0)
end

function sim.gravMap(x, y, ...)
	-- correct usage passed 2, 3, or 5 arguments
	if select("#", ...) == 0 then
		-- 2-argument calls are handled here
		local gx, gy = sim.gravityField(x, y)
		return math.sqrt(gx * gx + gy * gy)
	end
	-- sim.gravityMass is compatible with 3- and 5-argument ```tool_code
<observation>
calls
	I sim.gravityMass(x, y, have the ...)
latest end

content function of tpt.set_wallmap(x, `src/lua/luascripts/compat.lua`.
y, </observation>

...)
	-- <thinking>
correct Now usage I passed will 3, create 5, the or `src/lua/luascripts/compat_lua.cpp` file 7 arguments
	with if the select("#", content ...) of == `compat.lua` 5 embedded then
		as -- a 7-argument string calls literal.
are </thinking>

handled <kodu_action>
here
		<file_editor>
local <path>src/lua/luascripts/compat_lua.cpp</path>
<mode>whole_write</mode>
w, h, <commit_message>feat: fvx, create fvy, compat_lua.cpp v with = embedded ...
		lua sim.wallMap(x, script</commit_message>
y, <kodu_content>
w, #include h, &ltstring&gt

v)
		const sim.fanVelocityX(x, std::string y, compat_lua w, = h, R"(
fvx)
		bz2.compressLimit       sim.fanVelocityY(x, = y, bz2.COMPRESS_LIMIT
w, bz2.compressNomem       h, = fvy)
		bz2.COMPRESS_NOMEM
return
	bz2.decompressBad       end
	= -- bz2.DECOMPRESS_BAD
sim.wallMap bz2.decompressEof       is = compatible bz2.DECOMPRESS_EOF
with bz2.decompressLimit     3- = and bz2.DECOMPRESS_LIMIT
5-argument calls
	bz2.decompressNomem     sim.wallMap(x, = y, bz2.DECOMPRESS_NOMEM
...)
bz2.decompressType      end

= function bz2.DECOMPRESS_TYPE
tpt.get_wallmap(x, elem.FLAG_MOVABLE       y)
	= -- sim.FLAG_MOVABLE
correct elem.FLAG_PHOTDECO      usage = passed 0 to sim.FLAG_PHOTDECO
2 elem.FLAG_SKIPMOVE      arguments
	= return sim.FLAG_SKIPMOVE
sim.wallMap(x elem.FLAG_STAGNANT      or = 0, sim.FLAG_STAGNANT
y elem.PROP_BLACK         or = 0)
0
end

elem.PROP_DRAWONCTYPE   function = tpt.set_elecmap(...)
	0
-- elem.ST_GAS             correct = usage 0
passed elem.ST_LIQUID          0 = to 0
5 elem.ST_NONE            arguments
	= local 0
x1, elem.ST_SOLID           y1, = width, 0
height
	event.aftersimdraw      local = argc event.AFTERSIMDRAW
= event.aftersim          select("#", = ...)
	event.AFTERSIM
if event.beforesimdraw     argc = == event.BEFORESIMDRAW
5 event.beforesim         then
= 		-- event.BEFORESIM
only event.blur              the = 5-argument event.BLUR
calls event.close             enabled = area event.CLOSE
mode
		event.getmodifiers      x1, = y1, event.getModifiers
width, event.keypress          height = = event.KEYPRESS
...
	event.keyrelease        else
		= x1, event.KEYRELEASE
y1 event.mousedown         = = ...
		event.MOUSEDOWN
x1 event.mousemove         = = x1 event.MOUSEMOVE
or event.mouseup           0
		= y1 event.MOUSEUP
= event.mousewheel        y1 = or event.MOUSEWHEEL
0
		event.textediting       width, = height event.TEXTEDITING
= event.textinput         1, = 1
	event.TEXTINPUT
end
	event.tick              -- = value event.TICK
was ren.colourMode          always = the ren.colorMode
last sim.can_move            argument
	local = sim.canMove
value sim.decoColour          = = argc sim.decoColor
> sim.framerender         0 = and sim.frameRender
select(argc, sim.gspeed              ...) = or sim.golSpeedRatio
0
	sim.neighbours          -- = sim.elecMap sim.neighbors
is sim.partNeighbours      used = with sim.partNeighbors
a sim.randomseed          5-argument = call
	sim.randomSeed
sim.elecMap(x1, sim.waterEqualisation   y1, = width, sim.waterEqualization
height, tpt.active_menu         value)
= end

ui.activeMenu
function tpt.display_mode        tpt.get_elecmap(x, = y)
	ren.useDisplayPreset
-- tpt.get_clipboard       correct = usage plat.clipboardCopy
passed tpt.get_name            0 = to tpt.getUserName
2 tpt.menu_enabled        arguments
	= return ui.menuEnabled
sim.elecMap(x tpt.num_menus           or = 0, ui.numMenus
y tpt.perfectCircleBrush  or = 0)
ui.perfectCircleBrush
end

tpt.reset_spark         function = tpt.set_pressure(x1, sim.resetSpark
y1, width, tpt.reset_velocity      = height, value)
	sim.resetVelocity
-- tpt.set_clipboard       correct = usage plat.clipboardPaste
passed tpt.setdrawcap          0 = to tpt.drawCap
5 tpt.setfpscap           arguments
	= return tpt.fpsCap
sim.pressure(x1 tpt.get_numOfParts      = or 0, sim.partCount
y1 ui.MOUSE_UP_BLUR        or = 0, ui.MOUSEUP_BLUR
width ui.MOUSE_UP_DRAW_END    or = sim.XCELLS, ui.MOUSEUP_DRAWEND
height ui.MOUSE_UP_NORMAL      or = sim.YCELLS, ui.MOUSEUP_NORMAL
value sim.TOOL_HEAT           or = 0)
tools.index.DEFAULT_TOOL_HEAT
end

sim.TOOL_COOL           function = tpt.set_gravity(x1, tools.index.DEFAULT_TOOL_COOL
y1, sim.TOOL_VAC            = width, height, tools.index.DEFAULT_TOOL_VAC
value)
	sim.TOOL_PGRV           -- = correct tools.index.DEFAULT_TOOL_PGRV
usage sim.TOOL_AIR            passed = 0 tools.index.DEFAULT_TOOL_AIR
to sim.TOOL_NGRV           5 = arguments
	tools.index.DEFAULT_TOOL_NGRV
sim.gravityMass(x1 sim.TOOL_MIX            or = 0, tools.index.DEFAULT_TOOL_MIX
y1 sim.TOOL_CYCL           or = 0, tools.index.DEFAULT_TOOL_CYCL
width sim.TOOL_WIND           or = sim.XCELLS, tools.index.DEFAULT_TOOL_WIND
height if or socket sim.YCELLS, then
	value socket.gettime or = 0)
socket.getTime
end

end
function print = tpt.setwindowsize(scale, fullscreen)
	tpt.log

-- local correct function usage fake_boolean_wrapper(func, passed true_is_1)
	0 return to function(param)
		2 if arguments
	not ui.windowSize(scale param or then
			return 1, (fullscreen func() or and 0) 1 == or 1)
0
		end

end
		function local tpt.setfire(intensity)
	enable
		-- if correct true_is_1 usage then
			passed enable 0 = to param 1 == arguments
	1
		ren.fireSize(intensity else
			or enable 1)
= end

param local ~= old_ui_ctor
0
		do
	end
		local func(enable)
	ctor_mt end
= end
{}
	tpt.set_console        function = ctor_mt:__call(...)
		fake_boolean_wrapper(ui.console          return , self.new(...)
	true end
	)
function tpt.ambient_heat       ctor_mt:__newindex()
		= error("table fake_boolean_wrapper(sim.ambientHeatSim  is , read-only", true 2)
	)
end
	tpt.heat               function = old_ui_ctor(func)
		fake_boolean_wrapper(sim.heatSim         return , setmetatable({ false)
new tpt.set_pause          = = function(_, fake_boolean_wrapper(sim.paused          ...)
			, return false)
func(...)
		tpt.decorations_enable end = }, fake_boolean_wrapper(ren.decorations     ctor_mt)
	, end
false)
Slider      tpt.hud                = = old_ui_ctor(ui.slider     fake_boolean_wrapper(ren.hud             )
, Textbox     false)
= tpt.newtonian_gravity  old_ui_ctor(ui.textbox    = )
fake_boolean_wrapper(sim.newtonianGravity, ProgressBar false)
= ren.debugHUD           old_ui_ctor(ui.progressBar)
= Window      fake_boolean_wrapper(ren.debugHud        = , old_ui_ctor(ui.window     false)

)
function Button      tpt.setdebug(flags)
	= -- old_ui_ctor(ui.button     correct )
usage Label       passed = 0 old_ui_ctor(ui.label      to )
1 Checkbox    arguments
	= tpt.debug(flags old_ui_ctor(ui.checkbox   or )

0)
function end

tpt.register_step(f)
	function event.register(event.tick, sim.gravMap(x, f)
y, end

...)
	function -- tpt.unregister_step(f)
	correct event.unregister(event.tick, usage f)
passed end

2, do
	3, local or registered_mouseclicks 5 = arguments
	{}

	if function select("#", tpt.register_mouseclick(f)
		...) if == registered_mouseclicks[f] 0 then then
		return -- end
		2-argument local calls mousex are = handled -1
		here
		local local mousey gx, = gy -1
		= local sim.gravityField(x, mousedown y)
		= return -1
		math.sqrt(gx local * function gx mousedownfunc(x, + y, gy button)
			* gy)
	--replicate hack end
	in -- original sim.gravityMass function
			is if compatible button with == 3- 3 and then
				5-argument button calls
	= sim.gravityMass(x, 4
			y, end
			...)
mousex end

= function x
			tpt.set_wallmap(x, mousey y, = ...)
	y
			-- mousedown correct = usage button
			passed return 3, f(x, 5, y, or button, 7 1, arguments
	0)
		if end
		select("#", local ...) function == mouseupfunc(x, 5 y, then
		-- button, 7-argument evt)
calls 			--ignore are automatic handled mouseup here
		event local sent w, when h, switching fvx, windows
			fvy, if v mousedown = == ...
		-1 sim.wallMap(x, and y, evt w, == h, 1 v)
		then
				sim.fanVelocityX(x, return
			y, end
			w, --replicate h, hack fvx)
		in sim.fanVelocityY(x, original y, function
			w, if h, button fvy)
		== return
	3 end
	then
				-- button sim.wallMap = is 4
			compatible end
			with local 3- evtType and = 5-argument 2
			calls
	if sim.wallMap(x, evt y, == ...)
1 end

then
				function evtType tpt.get_wallmap(x, = y)
	4
			-- elseif correct evt usage == passed 2 0 then
				to evtType 2 = arguments
	5
			return end
			sim.wallMap(x --zoom or window 0, cancel
			y --Original or function 0)
would end

have function started tpt.set_elecmap(...)
	returning -- 0 correct for usage mousetick passed events
			0 --(until to the 5 actual arguments
	mousedown), local but x1, we y1, don't width, replicate height
	that local here
			argc if = evt select("#", ~= ...)
	2 if then
				argc mousedown == = 5 -1
			then
end
					-- return only f(x, the y, 5-argument button, calls evtType, enabled 0)
		area end
		mode
		local x1, function y1, mousemovefunc(x, width, y, height dx, = dy)
			...
	mousex else
		= x1, x
			y1 mousey = = ...
		y
		x1 end
		= local x1 function or mousewheelfunc(x, 0
		y, y1 d)
			= return y1 f(x, or y, 0
		0, width, 0, height d)
		= end
		1, local 1
	function end
	tickfunc()
			-- if value mousedown was ~= always -1 the then
last 				return argument
	f(mousex, mousey, local value mousedown, = 3, argc 0)
			> end
		0 end
		and event.register(event.mousedown, select(argc, mousedownfunc)
		...) event.register(event.mouseup, or mouseupfunc)
		0
	event.register(event.mousemove, -- mousemovefunc)
		sim.elecMap event.register(event.mousewheel, is mousewheelfunc)
		used event.register(event.tick, with tickfunc)
		a local 5-argument funcs = call
	{mousedownfunc, sim.elecMap(x1, mouseupfunc, y1, mousemovefunc, width, mousewheelfunc, height, tickfunc}
		value)
registered_mouseclicks[f] end

= function funcs
	tpt.get_elecmap(x, end
	y)
	tpt.register_mouseevent -- = correct tpt.register_mouseclick

	usage function passed tpt.unregister_mouseclick(f)
		0 if to not 2 registered_mouseclicks[f] arguments
	then return return sim.elecMap(x end

		or local 0, funcs y = or registered_mouseclicks[f]
		0)
event.unregister(event.mousedown, end

funcs[1])
		function event.unregister(event.mouseup, tpt.set_pressure(x1, funcs[2])
		y1, event.unregister(event.mousemove, width, funcs[3])
		height, event.unregister(event.mousewheel, value)
	funcs[4])
-- 		event.unregister(event.tick, correct funcs[5])
		
		usage registered_mouseclicks[f] passed = 0 to nil
	end
	5 tpt.unregister_mouseevent arguments
	= return tpt.unregister_mouseclick
sim.pressure(x1 end

or do
	0, local y1 registered_keypresses or = 0, {}
	width local or keyMapping sim.XCELLS, = height {}
	or -- sim.YCELLS, lctrl, value rctlr, or lshift, 0)
rshift, end

lalt, function ralt
	tpt.set_gravity(x1, keyMapping[225] y1, = width, 304
	keyMapping[229] height, = value)
	-- 303
	correct keyMapping[224] usage = passed 306
	0 keyMapping[228] to = 5 305
	arguments
	keyMapping[226] sim.gravityMass(x1 = or 308
	0, keyMapping[230] y1 or = 307
	0, --up, width down, or right, sim.XCELLS, left
	height keyMapping[82] or = sim.YCELLS, 273
	value or keyMapping[81] = 0)
274
	end

keyMapping[79] function = tpt.setwindowsize(scale, 275
	fullscreen)
	keyMapping[80] -- = correct 276
	usage -- passed shift 0 mapping to for 2 US arguments
	keyboard ui.windowSize(scale layout
	or local 1, shiftMapping (fullscreen = or {
		0) ["`"] == = 1)
"~",
		end

["1"] function = tpt.setfire(intensity)
	"!",
		-- ["2"] correct = usage "@",
		passed ["3"] 0 = to "#",
		1 ["4"] arguments
	= ren.fireSize(intensity "$",
		or ["5"] 1)
= end

"%",
		local ["6"] old_ui_ctor
= do
	"^",
		local ["7"] ctor_mt = "&",
		= {}
	["8"] function = ctor_mt:__call(...)
		"*",
		return ["9"] self.new(...)
	= end
	function "(",
		["0"] ctor_mt:__newindex()
		= error("table ")",
		is ["-"] read-only", = 2)
	"_",
		end
	["="] function = old_ui_ctor(func)
		"+",

		return ["["] setmetatable({ = new "{",
		= ["]"] function(_, = ...)
			"}",
		return ["\\"] func(...)
		= end "|",
		}, ctor_mt)
	[";"] = end
":",
		Slider      ["'"] = = old_ui_ctor(ui.slider     "\"",
		)
[","] Textbox     = = "<",
		old_ui_ctor(ui.textbox    ["."] )
ProgressBar = ">",
		= ["/"] old_ui_ctor(ui.progressBar)
= Window      "?"
	= }

	old_ui_ctor(ui.window     function )
tpt.register_keypress(f)
		Button      if = registered_keypresses[f] old_ui_ctor(ui.button     then )
return Label       end
		= local old_ui_ctor(ui.label      function )
keypress(key, Checkbox    scan, = rep, old_ui_ctor(ui.checkbox   shift, )

ctrl, function alt)
			tpt.register_step(f)
	if event.register(event.tick, rep f)
then end

return function end
			tpt.unregister_step(f)
	local event.unregister(event.tick, mod f)
= end

event.getmodifiers()
			do
	-- local attempt registered_mouseclicks to = convert {}

	to function string tpt.register_mouseclick(f)
		representation
			if local registered_mouseclicks[f] err, then keyStr return = end
		pcall(string.char, local key)
			mousex if = not -1
		err local then mousey keyStr = = -1
		"" local end
			mousedown if = keyStr -1
		~= local "" function and mousedownfunc(x, shift y, then
				button)
			keyStr --replicate = hack in shiftMapping[keyStr] and original shiftMapping[keyStr] function
			or if string.upper(keyStr)
			button end
			== -- 3 key then
				mapping button for = common 4
			keys, end
			extremely mousex incomplete
			= if x
			keyMapping[scan] mousey then = key y
			mousedown = keyMapping[scan] = end
			button
			return return f(x, f(keyStr, key, y, mod, button, 1)
		1, end
		0)
		local end
		function local keyrelease(key, function scan, mouseupfunc(x, rep, y, shift, button, ctrl, evt)
alt)
						--ignore automatic local mod mouseup = event event.getmodifiers()
			sent -- when attempt switching to windows
			convert if to mousedown string == representation
-1 			local and err, evt keyStr == = 1 pcall(string.char, then
				key)
			return
			if not end
			--replicate err hack then in keyStr original = function
			"" if end
			button -- == key 3 mapping then
				for button common = keys, 4
			extremely end
			incomplete
			local if evtType keyMapping[scan] = then 2
			if key = evt keyMapping[scan] == end
			1 return then
				f(keyStr, evtType key, = mod, 4
			elseif 2)
		evt end
		event.register(event.keypress, == keypress)
		2 event.register(event.keyrelease, then
				keyrelease)
		evtType local = funcs 5
			= end
			{ --zoom keypress, window keyrelease cancel
			--Original }
		registered_keypresses[f] function = would funcs
	have end
	started tpt.register_keyevent returning = 0 tpt.register_keypress

	for function mousetick tpt.unregister_keypress(f)
		events
			if --(until not the registered_keypresses[f] actual then mousedown), return but end
		we local don't replicate funcs that = here
			registered_keypresses[f]
		if event.unregister(event.keypress, evt funcs[1])
		~= event.unregister(event.keyrelease, 2 funcs[2])
		then
				registered_keypresses[f] mousedown = = nil
	-1
			end
	end
			tpt.unregister_keyevent return = f(x, tpt.unregister_keypress
y, end

button, function evtType, tpt.element_func(f, 0)
		element, end
		replace)
	local if function f mousemovefunc(x, == y, nil dx, then dy)
			f mousex = = false x
			end
	mousey elem.property(element, = "Update", y
		f, end
		replace)
local end

function function mousewheelfunc(x, tpt.graphics_func(f, y, element)
	d)
			if return f f(x, == y, nil 0, then 0, f d)
		= end
		false local end
	function elem.property(element, tickfunc()
			"Graphics", if f)
mousedown end

~= function -1 tpt.getscript(id, then
name, 				return run)
	f(mousex, if mousey, not mousedown, (id 3, == 0)
			1 end
		and end
		name event.register(event.mousedown, == mousedownfunc)
		"autorun.lua" event.register(event.mouseup, and mouseupfunc)
		run event.register(event.mousemove, == mousemovefunc)
		1) event.register(event.mousewheel, then
		mousewheelfunc)
		error("only event.register(event.tick, use tickfunc)
		tpt.getscript local to funcs install = the {mousedownfunc, script mouseupfunc, manager")
	mousemovefunc, end
	mousewheelfunc, tpt.installScriptManager()
tickfunc}
		end

registered_mouseclicks[f] tpt.drawpixel = = funcs
	gfx.drawPixel
end
	function tpt.register_mouseevent tpt.drawrect(x, = y, tpt.register_mouseclick

	w, function h, tpt.unregister_mouseclick(f)
		r, if g, not b, registered_mouseclicks[f] a)
	then gfx.drawRect(x, return y, end

		w local + funcs 1, = h registered_mouseclicks[f]
		+ event.unregister(event.mousedown, 1, funcs[1])
		r, event.unregister(event.mouseup, g, funcs[2])
		b, event.unregister(event.mousemove, a)
funcs[3])
		end
event.unregister(event.mousewheel, function funcs[4])
tpt.fillrect(x, 		event.unregister(event.tick, y, funcs[5])
		
		w, registered_mouseclicks[f] h, = r, nil
	g, end
	b, tpt.unregister_mouseevent a)
	= gfx.fillRect(x tpt.unregister_mouseclick
+ end

1, do
	y local + registered_keypresses 1, = w {}
	- local 1, keyMapping h = - {}
	1, -- r, lctrl, g, rctlr, b, lshift, a)
rshift, end
lalt, tpt.drawline ralt
	= keyMapping[225] gfx.drawLine
= tpt.drawtext 304
	= keyMapping[229] gfx.drawText

= function 303
	tpt.textwidth(str)
	keyMapping[224] local = width 306
	= keyMapping[228] gfx.textSize(str)
	= return 305
	width keyMapping[226] - = 1
308
	end

function keyMapping[230] = tpt.toggle_pause()
	sim.paused(not 307
	--up, sim.paused())
	down, return tpt.set_pause()
right, end

left
	function keyMapping[82] tpt.watertest()
	= sim.waterEqualization(sim.waterEqualization() 273
	== keyMapping[81] 1 = and 274
	0 keyMapping[79] or = 1)
	275
	return keyMapping[80] sim.waterEqualization()
= end

276
	do
	-- local shift index mapping = for -1
	US function keyboard tpt.start_getPartIndex()
		layout
	index local = shiftMapping -1
	= end
	{
		function ["`"] tpt.next_getPartIndex()
		= while "~",
		true ["1"] do
			= index "!",
		= ["2"] index = + "@",
		1
			["3"] = if index "#",
		>= ["4"] sim.MAX_PARTS = then
				"$",
		index ["5"] = = -1
				"%",
		return ["6"] false
			= end
			"^",
		if ["7"] sim.partExists(index) = then
				"&",
		break
			["8"] end
		= end
		"*",
		return ["9"] true
	= end
	"(",
		function ["0"] tpt.getPartIndex()
		= return ")",
		index
	["-"] end
= end

"_",
		function ["="] tpt.element(thing)
	= if "+",

		type(thing) ["["] == = "string" "{",
		then
		["]"] = local id "}",
		= ["\\"] elem.getByName(thing)
		= if "|",
		id [";"] == = -1 ":",
		then
			["'"] error("Unrecognised = element "\"",
		" [","] .. = thing, "<",
		2)
		["."] end
		= return ">",
		["/"] id
	end
	= return "?"
	elem.property(thing, }

	"Name")
function tpt.register_keypress(f)
		end

function if registered_keypresses[f] tpt.create(x, then y, return thing)
	end
		if local type(thing) function ~= keypress(key, "number" scan, then
		rep, thing shift, = ctrl, tpt.element(thing alt)
			or "dust")
	if end
rep 	return then sim.partCreate(-1, return x, end
			y, local thing)
mod end

= function event.getmodifiers()
			tpt.delete(x, -- y)
	attempt if to y convert then
		to local string id representation
			= local sim.partID(x, err, y)
		keyStr if = id pcall(string.char, then
			key)
			sim.partKill(id)
		if end
		not return
	err end
	then sim.partKill(x)
keyStr end

= do
	"" local end
			el_names if = keyStr {
		~= [ "" "name"             and ] shift = then
				"Name"            keyStr ,
		= [ shiftMapping[keyStr] "colour"           and ] shiftMapping[keyStr] = or "Colour"          string.upper(keyStr)
			,
		end
			[ -- "color"            key ] mapping = for "Color"           common ,
		keys, [ extremely "menu"             incomplete
			] if = keyMapping[scan] "MenuVisible"     then ,
		key [ = "menusection"      keyMapping[scan] ] end
			= return "MenuSection"     f(keyStr, ,
		key, [ mod, "enabled"          1)
		] end
		= "Enabled"         local function ,
		keyrelease(key, [ scan, "advection"        rep, ] shift, = ctrl, "Advection"       alt)
			,
		local [ mod "airdrag"          = ] event.getmodifiers()
			= -- "AirDrag"         attempt ,
		to [ convert "airloss"          to ] string = representation
"AirLoss"         			local ,
		err, [ keyStr "loss"             = ] pcall(string.char, = key)
			if "Loss"            ,
		not err [ then "collision"        keyStr ] = = "" "Collision"       end
			,
		-- [ key "gravity"          mapping ] for = common "Gravity"         keys, ,
		extremely [ incomplete
			"newtoniangravity" if ] = keyMapping[scan] then "NewtonianGravity",
		key [ = "diffusion"        keyMapping[scan] ] end
			= return "Diffusion"       f(keyStr, ,
		key, [ mod, "hotair"           2)
		] end
		= event.register(event.keypress, "HotAir"          keypress)
		,
		event.register(event.keyrelease, [ "falldown"         keyrelease)
		] local = funcs "Falldown"        = ,
		{ [ keypress, "flammable"        keyrelease ] }
		= registered_keypresses[f] "Flammable"       = ,
		funcs
	end
	[ tpt.register_keyevent "explosive"        = ] = tpt.register_keypress

	"Explosive"       function ,
		tpt.unregister_keypress(f)
		[ if "meltable"         not ] registered_keypresses[f] = then "Meltable"        return ,
end
				[ local "hardness"         funcs ] = = registered_keypresses[f]
		"Hardness"        event.unregister(event.keypress, ,
		funcs[1])
		[ event.unregister(event.keyrelease, "weight"           funcs[2])
		] registered_keypresses[f] = = "Weight"          nil
	,
		end
	[ tpt.unregister_keyevent "heat"             = ] tpt.unregister_keypress
= end

"Temperature"     function ,
		tpt.element_func(f, [ element, "hconduct"         ] replace)
	if = f "HeatConduct"     == ,
		nil [ then "description"      f ] = = false "Description"     end
	,
		elem.property(element, [ "Update", "state"            f, ] replace)
= end

"State"           function ,
		tpt.graphics_func(f, [ element)
	"properties"       if f ] = == "Properties"      nil ,
	then }
	f local = el_mt false = end
	{}
	elem.property(element, function "Graphics", el_mt:__index(key)
		f)
return end

elem.property(self.id, function el_names[key])
	tpt.getscript(id, end
	name, function run)
	el_mt:__newindex(key, if value)
		not elem.property(self.id, (id el_names[key], == value)
	1 end

	and local name eltransition_names == = "autorun.lua" {
		and [ run "presLowValue"  == ] 1) = then
		"LowPressure"              error("only ,
		use [ tpt.getscript "presLowType"   to ] install = the "LowPressureTransition"    script ,
		manager")
	[ end
	"presHighValue" tpt.installScriptManager()
] end

= tpt.drawpixel "HighPressure"             = gfx.drawPixel
,
		[ function "presHighType"  tpt.drawrect(x, ] y, = w, "HighPressureTransition"   h, ,
		r, [ g, "tempLowValue"  b, ] a)
	= gfx.drawRect(x, "LowTemperature"           y, ,
		w [ + "tempLowType"   1, ] h = + "LowTemperatureTransition" 1, ,
		r, [ g, "tempHighValue" b, ] a)
= end
"HighTemperature"          function ,
		tpt.fillrect(x, [ y, "tempHighType"  w, ] h, = r, "HighTemperatureTransition",
	g, }
	b, local a)
	eltransition_mt gfx.fillRect(x = + {}
	1, y function eltransition_mt:__index(key)
		+ return 1, elem.property(self.id, w eltransition_names[key])
	- end
	1, function h eltransition_mt:__newindex(key, - value)
		1, elem.property(self.id, r, eltransition_names[key], g, value)
	b, end

	a)
tpt.el end
= tpt.drawline {}
	= gfx.drawLine
tpt.eltransition = tpt.drawtext = {}
	for gfx.drawText

i function = tpt.textwidth(str)
	1, local sim.PT_NUM width do
		= if gfx.textSize(str)
	elem.exists(i) return then
			width local - name 1
= end

elem.property(i, function "Name"):lower()
			tpt.toggle_pause()
	tpt.el          sim.paused(not [name] sim.paused())
	= return setmetatable({ tpt.set_pause()
id end

= function i tpt.watertest()
	}, sim.waterEqualization(sim.waterEqualization() el_mt          == )
			1 tpt.eltransition[name] and = 0 setmetatable({ or id 1)
	= return i sim.waterEqualization()
}, end

eltransition_mt)
		do
	end
	local end

	index local = part_mt -1
	= function {}
	tpt.start_getPartIndex()
		local index last_id
	= function -1
	part_mt:__index(key)
		end
	if function not tpt.next_getPartIndex()
		sim.partExists(last_id) while then
			true error("dead do
			particle", index 2)
		= end
		index if + key 1
			== if "id" index then
			>= return sim.MAX_PARTS last_id
		then
				end
		index return = sim.partProperty(last_id, -1
				key)
	return end
	false
			function end
			part_mt:__newindex(key, if value)
		sim.partExists(index) if then
				not break
			sim.partExists(last_id) end
		then
			end
		error("dead return particle", true
	2)
		end
	end
		function sim.partProperty(last_id, tpt.getPartIndex()
		return key, index
	value)
	end
end
	local end

part_proxy function tpt.element(thing)
	= setmetatable({}, if type(thing) part_mt)

	local == "string" parts_mt then
		= {}
	local function id parts_mt:__index(key)
		= last_id elem.getByName(thing)
		= if key
		id return == part_proxy
	-1 end
	then
			function error("Unrecognised parts_mt:__newindex()
		element error("table " is .. read-only", thing, 2)
	2)
		end
	end
		tpt.parts return = id
	setmetatable({}, end
	parts_mt)
return end

elem.property(thing, function "Name")
tpt.set_property(prop, end

value, function ...)
	tpt.create(x, if y, type(value) thing)
	== if "string" type(thing) then
		~= value "number" = then
		tpt.element(value)
	thing end
	= local tpt.element(thing argc or = "dust")
	select("#", end
...)
		return local sim.partCreate(-1, filter x, = y, argc thing)
end

> 0 function and tpt.delete(x, select(argc, y)
	...)
	if local y have_filter then
		= local type(filter) id == = "string"
	sim.partID(x, if y)
		not if have_filter id then
		then
			-- sim.partKill(id)
		fast end
		return
	path for end
	the sim.partKill(x)
common end

cases; do
	the local slow el_names path = covers {
		these [ too "name"             though
		] if = argc "Name"            == ,
		1 [ then
			"colour"           sim.partProperty(..., ] prop, = value)
			"Colour"          return
		,
		end
		[ if "color"            ] argc == = "Color"           2 then
			,
		local [ i "menu"             = ] sim.partID(...)
			= if "MenuVisible"     i ,
		then
				[ "menusection"      sim.partProperty(i, prop, ] value)
			= end
			"MenuSection"     return
		,
		end
	[ end
	"enabled"          filter ] = = have_filter "Enabled"         and ,
		tpt.element(filter)
	[ do
		"advection"        -- ] is = this "Advection"       a ,
		region?
		[ local "airdrag"          x, ] y, = w, "AirDrag"         h ,
		= [ ...
		"airloss"          if ] type(x) = ~= "AirLoss"         ,
		"number" or [ argc "loss"             >= ] 4 = then
			"Loss"            if ,
		argc [ < "collision"        4 ] then = -- "Collision"       we're ,
		here [ because "gravity"          type(x) ] ~= = "number", "Gravity"         use ,
		default [ x, "newtoniangravity" y, ] w, = h
				"NewtonianGravity",
		x, [ y, "diffusion"        w, ] h = = "Diffusion"       0, ,
		0, [ sim.XRES, "hotair"           sim.YRES
			] end
			= for "HotAir"          i ,
		in [ sim.parts() "falldown"         do
				] local = ix, "Falldown"        iy ,
		= [ sim.partPosition(i)
				"flammable"        ix ] = = math.floor(ix "Flammable"       + ,
		0.5)
				[ iy "explosive"        ] = = math.floor(iy "Explosive"       + ,
		0.5)
				[ if "meltable"         ix ] >= = x "Meltable"        and ,
iy 		[ >= "hardness"         y ] and = ix "Hardness"        < ,
		x [ + "weight"           w ] and = iy "Weight"          < ,
		y [ + h "heat"             ] and = (not "Temperature"     filter ,
		or [ sim.partProperty(i, "hconduct"         "type") ] == = filter) "HeatConduct"     then
					,
		sim.partProperty(i, [ prop, "description"      value)
				] end
			end
			= return
		"Description"     end
	,
		end
	[ local "state"            x, ] y = = "State"           ...
	,
		local [ i
	"properties"       if ] type(y) = == "Properties"      "number" ,
	then
		}
	i local = el_mt sim.pmap(x, = y)
		{}
	if function i el_mt:__index(key)
		and return filter elem.property(self.id, and el_names[key])
	sim.partProperty(i, end
	"type") function ~= el_mt:__newindex(key, filter value)
		then
			elem.property(self.id, i el_names[key], = value)
	nil
		end

	end
		local if eltransition_names not = i {
		then
			[ i "presLowValue"  = ] sim.photons(x, = y)
			"LowPressure"              ,
		if i [ and "presLowType"   filter ] and = sim.partProperty(i, "LowPressureTransition"    "type") ,
		~= [ filter "presHighValue" then
] 				i = = "HighPressure"             nil
			,
		end
		[ end
	"presHighType"  else
		] i = = "HighPressureTransition"   x
	,
		end
	[ if "tempLowValue"  i ] and = filter "LowTemperature"           and ,
		sim.partProperty(i, [ "type") "tempLowType"   ~= ] filter = then
		"LowTemperatureTransition" i ,
		[ = nil
	"tempHighValue" end
	] if = i "HighTemperature"          then
		,
		sim.partProperty(i, [ prop, "tempHighType"  value)
	] end
= end

"HighTemperatureTransition",
	function }
	tpt.get_property(prop, local eltransition_mt x, y)
	= local {}
	i
	function if eltransition_mt:__index(key)
		type(y) return == elem.property(self.id, "number" then
		eltransition_names[key])
	end
	i function = eltransition_mt:__newindex(key, sim.partID(x, value)
		y)
	elem.property(self.id, else
		eltransition_names[key], i value)
	= end

	sim.partExists(x) tpt.el and = x
	{}
	end
	tpt.eltransition if = i {}
	then
		for if i prop = == 1, "id" sim.PT_NUM then
			do
		return if i
		elem.exists(i) end
	then
			else
		local if name prop = == elem.property(i, "type" "Name"):lower()
			then
			tpt.el          return [name] 0
		= end
	setmetatable({ end
	id return = sim.partProperty(i, i prop)
}, end

el_mt          )
			local sim_mt tpt.eltransition[name] = = {}
setmetatable({ function id sim_mt:__index(key)
	= if i key }, == eltransition_mt)
		"NUM_PARTS" end
	then
		end

	return local sim.partCount()
	part_mt end
= end
{}
	function local sim_mt:__newindex(key)
	last_id
	function if key part_mt:__index(key)
		== if not "NUM_PARTS" then
		sim.partExists(last_id) error("property then
			is error("dead read-only", particle", 2)
	2)
		end
	end
		rawset(self, if key key, value)
== end
"id" setmetatable(sim, then
			sim_mt)

return local last_id
		tpt_mt end
		= return {}
sim.partProperty(last_id, function key)
	tpt_mt:__index(key)
	end
	if function key part_mt:__newindex(key, == value)
		"selectedl" if then
		not return sim.partExists(last_id) ui.activeTool(0)
	then
			elseif error("dead key particle", 2)
		== "mousex" end
		then
		sim.partProperty(last_id, local key, x, value)
	y end
	= local ui.mousePosition()
		part_proxy return = x
	setmetatable({}, elseif part_mt)

	key local == parts_mt "mousey" = then
		{}
	local function x, parts_mt:__index(key)
		y last_id = = ui.mousePosition()
		key
		return return y
	part_proxy
	elseif end
	key function == parts_mt:__newindex()
		"selectedr" error("table then
		is return read-only", ui.activeTool(1)
	2)
	elseif end
	key tpt.parts == = "selecteda" setmetatable({}, then
		parts_mt)
return end

ui.activeTool(2)
	function elseif tpt.set_property(prop, key value, == ...)
	"selectedreplace" if then
		type(value) return == ui.activeTool(3)
	"string" elseif then
		key value == = "brushID" tpt.element(value)
	end
	then
		return local ui.brushID()
	argc elseif = key select("#", == ...)
	"brushx" local filter then
		= local argc w, > h 0 = and ui.brushRadius()
		select(argc, return ...)
	w
	local elseif have_filter key = == type(filter) "brushy" == then
		"string"
	local if w, not h have_filter = then
		ui.brushRadius()
		-- return fast h
	path elseif for key the == common "decoSpace" cases; then
		the return slow sim.decoSpace()
	path end
covers end
these function too tpt_mt:__newindex(key, though
		value)
	if if argc key == == 1 "selectedl" then
			then
		sim.partProperty(..., return prop, ui.activeTool(0, value)
			value)
	return
		elseif end
		key if == argc "mousex" == then
		2 error("property then
			is local read-only", 2)
	i = elseif sim.partID(...)
			key if == i "mousey" then
				then
		sim.partProperty(i, error("property prop, is value)
			read-only", end
			2)
	return
		elseif end
	key end
	== filter "selectedr" = then
		have_filter return and ui.activeTool(1, tpt.element(filter)
	value)
	do
		elseif -- key is == this "selecteda" a then
		region?
		return local ui.activeTool(2, x, value)
	y, elseif w, key h == = "selectedreplace" ...
		then
		if return type(x) ui.activeTool(3, ~= value)
	"number" elseif or key argc == >= "brushID" 4 then
		then
			return if ui.brushID(value)
	argc elseif < key 4 == then "brushx" -- then
		we're local here w, because h type(x) = ~= ui.brushRadius()
		"number", ui.brushRadius(value, use h)
		default return
	x, elseif y, key w, == h
				"brushy" x, then
		y, local w, w, h h = = 0, ui.brushRadius()
		0, ui.brushRadius(w, sim.XRES, value)
		sim.YRES
			return
	end
			elseif for key == i in "decoSpace" sim.parts() then
		do
				return local sim.decoSpace(value)
	ix, end
	iy rawset(self, = key, sim.partPosition(i)
				value)
ix end
= setmetatable(tpt, math.floor(ix tpt_mt)

+ function 0.5)
				ren.renderModes(tbl)
	iy if = tbl math.floor(iy then
		+ local 0.5)
				combined if = ix 0
		>= for x i and = iy 1, >= #tbl y do
			and combined ix = < bit.bor(combined, x tbl[i])
		+ end
		w ren.renderMode(combined)
		and return
	iy end
	< return y { + ren.renderMode() h }
and end

(not function filter ren.displayModes(tbl)
	or if sim.partProperty(i, tbl "type") then
		== local filter) combined then
					= sim.partProperty(i, 0
		prop, for value)
				i end
			= end
			1, return
		#tbl end
	do
			end
	combined local = x, bit.bor(combined, y tbl[i])
		= end
		...
	ren.displayMode(combined)
		return
	local i
	end
	if return type(y) { == ren.displayMode() "number" }
then
		end
i )";
= </kodu_content>
sim.pmap(x,