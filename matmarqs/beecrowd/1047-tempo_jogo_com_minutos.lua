local h1 = io.read("*n")
local m1 = io.read("*n")

local t1 = 60 * h1 + m1

local h2 = io.read("*n")
local m2 = io.read("*n")

local t2 = 60 * h2 + m2

local t = t2 - t1

if t < 1 then
	t = t + 24 * 60
end

local h = math.floor(t / 60)
local m = t - 60 * h

print(string.format("O JOGO DUROU %d HORA(S) E %d MINUTO(S)", h, m))
