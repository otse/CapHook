local player = GetLocalPlayerId();
local xPos = CAPI_Entity.GetEntityPosition(player, 0);
local yPos = CAPI_Entity.GetEntityPosition(player, 1);
local zPos = CAPI_Entity.GetEntityPosition(player, 2);

local ID = "9015359081802239";
local Prop = SpawnEntityFromArchetype_Legacy(ID, xPos, yPos, zPos, 0, 0, 0);
asdsd