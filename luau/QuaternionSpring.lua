--!strict
--[[
    Source: https://github.com/probablytukars/LuaQuaternion
    Based on: https://github.com/Quenty/NevermoreEngine/tree/main/src/spring
    [MIT LICENSE]
]]

local Quaternion = require(script.Parent.Quaternion)
type Quaternion = Quaternion.Quaternion
local ERROR_FORMAT = "%q is not a valid member of QuaternionSpring."

local QuaternionSpring = {_type = "QuaternionSpring"}

type t_QuaternionSpring = {
	new: (initial: Quaternion, damping: number, speed: number, clock: () -> number) -> QuaternionSpring,
	Reset: (target: Quaternion?) -> nil,
	Impulse: (self: QuaternionSpring, velocity: Vector3) -> nil,
	TimeSkip: (self: QuaternionSpring, delta: number) -> nil,
	
	Position: Quaternion,
	p: Quaternion,
	Velocity: Vector3,
	v: Vector3,
	Target: Quaternion,
	t: Quaternion,
	Damping: number,
	d: number,
	Speed: number,
	s: number,
	Clock: () -> number,
	
	_clock: () -> number,
	_time: number,
	_position:  Quaternion,
	_velocity:  Vector3,
	_target:  Quaternion,
	_damping:  number,
	_speed:  number,
	_initial:  Quaternion,
}

export type QuaternionSpring = typeof(setmetatable({} :: t_QuaternionSpring, QuaternionSpring))

--[=[
    @class QuaternionSpring
    @grouporder ["Constructors", "Methods"]
    
    This class represents a rotational spring using Quaternions.
    Velocity is a Vector3 where the magnitude is the angle, and the unit
    is the axis (if angle is > 0).
    
    This is lazily evaluated meaning it only updates when indexed.
--]=]
--[=[
    @prop Position nlerpable
    
    The current position (rotation) at the given clock time. 
    Assigning the position will change the spring to have that position.
--]=]
--[=[
    @prop p nlerpable
    @alias Position
--]=]
--[=[
    @prop Velocity nlerpable
    
    The current velocity. Assigning the velocity will change the spring to have 
    that velocity. The velocity should be in the axis with angle magnitude
    format, where the magnitude represents the angle, and the unit of that
    vector (if magnitude is > 0) represents the axis of rotation.
    The zero vector represents no velocity.
--]=]
--[=[
    @prop v nlerpable
    @alias Velocity
--]=]
--[=[
    @prop Target nlerpable
    
    The current target. Assigning the target will change the spring to have 
    that target.
--]=]
--[=[
    @prop t nlerpable
    @alias Target
--]=]
--[=[
    @prop Damping number
    
    The current damper, defaults to 1. At 1 the spring is critically damped. 
    At less than 1, it will be underdamped, and thus, bounce, and at over 1, 
    it will be critically damped.
--]=]
--[=[
    @prop d number
    @alias Damping
--]=]
--[=[
    @prop Speed number
    
    The speed, defaults to 1, but should be between [0, infinity)
--]=]
--[=[
    @prop s number
    @alias Speed
--]=]
--[=[
    @prop Clock
]=]


--[=[
    @function
    @group Constructors
    
    Constructs a new Quaternion Spring at the position and target specified.
]=]
function QuaternionSpring.new(initial: Quaternion?, damping: number?, speed: number?, clock: (() -> number)?): QuaternionSpring
	local l_initial = initial or Quaternion.identity
	local l_damping = damping or 1
	local l_speed = speed or 1
	local l_clock = clock or os.clock
	
	local self = {
		_clock = l_clock,
		_time = l_clock(),
		_position = l_initial,
		_velocity = Vector3.zero,
		_target = l_initial,
		_damping = l_damping,
		_speed = l_speed,
		_initial = l_initial
	}
	
	return setmetatable(self :: t_QuaternionSpring, QuaternionSpring)
end

--[=[
    @method
    @group Methods
    
    Resets the springs' position and target to the target value provided, or 
    to the initial value the spring was created with if target is not specified.
    Sets the velocity to zero.
]=]

local function Reset(self: QuaternionSpring, target: Quaternion?)
	local setTo = target or self._initial
	self._position = setTo
	self._target = setTo
	self._velocity = Vector3.zero
end

QuaternionSpring.Reset = Reset

--[=[
    @method
    @group Methods
    
    Impulses the spring, increasing velocity by the amount given.
    This is useful to make something shake. Note that the velocity
    will be a rotation vector, such that the axis is the direction
    and the magnitude is the angle (compact axis-angle).
]=]




local function Impulse(self: QuaternionSpring, velocity: Vector3)
	self._velocity = self._velocity + velocity
end

QuaternionSpring.Impulse = Impulse


local function _positionVelocity(self: QuaternionSpring, now: number)
	local currentRotation = self._position
	local currentVelocity = self._velocity
	local targetRotation = self._target
	local dampingFactor = self._damping
	local speed = self._speed
	
	local deltaTime = speed * (now - self._time)
	local dampingSquared = dampingFactor * dampingFactor
	
	local angFreq, sinTheta, cosTheta
	if dampingSquared < 1 then
		angFreq = math.sqrt(1 - dampingSquared)
		local exponential = math.exp(-dampingFactor * deltaTime) / angFreq
		cosTheta = exponential * math.cos(angFreq * deltaTime)
		sinTheta = exponential * math.sin(angFreq * deltaTime)
	elseif dampingSquared == 1 then
		angFreq = 1
		local exponential = math.exp(-dampingFactor * deltaTime)
		cosTheta, sinTheta = exponential, exponential * deltaTime
	else
		angFreq = math.sqrt(dampingSquared - 1)
		local angFreq2 = 2 * angFreq
		local u = math.exp((-dampingFactor + angFreq) * deltaTime) / angFreq2
		local v = math.exp((-dampingFactor - angFreq) * deltaTime) / angFreq2
		cosTheta, sinTheta = u + v, u - v
	end
	
	local pullToTarget = 1 - (angFreq * cosTheta + dampingFactor * sinTheta)
	local velPosPush = sinTheta / speed
	local velPushRate = speed * sinTheta
	local velocityDecay = angFreq * cosTheta - dampingFactor * sinTheta
	
	local posQuat = currentRotation:Slerp(targetRotation, pullToTarget)
	local newPosition = posQuat:Integrate(currentVelocity, velPosPush)
	
	local difQuat = currentRotation:Difference(targetRotation)
	local axis, angle = difQuat:ToAxisAngle()
	local velPush = (axis * angle) * velPushRate
	local velDecay = currentVelocity * velocityDecay
	
	local newVelocity = velPush + velDecay
	
	return newPosition, newVelocity
end

--[=[
    @method
    @group Methods
    Instantly skips the spring forwards by the given time.
]=]
local function TimeSkip(self: QuaternionSpring, delta: number)
	local now = self._clock()
	local position, velocity = _positionVelocity(self, now+delta)
	self._position = position
	self._velocity = velocity
	self._time = now
end

QuaternionSpring.TimeSkip = TimeSkip

function QuaternionSpring.__index(self: QuaternionSpring, index: string)
	if QuaternionSpring[index] then
		return QuaternionSpring[index]
	elseif index == "Position" or index == "p" then
		local position, _ = _positionVelocity(self, self._clock())
		return position
	elseif index == "Velocity" or index == "v" then
		local _, velocity = _positionVelocity(self, self._clock())
		return velocity
	elseif index == "Target" or index == "t" then
		return self._target
	elseif index == "Damping" or index == "d" then
		return self._damping
	elseif index == "Speed" or index == "s" then
		return self._speed
	elseif index == "Clock" then
		return self._clock
	end
	error(string.format(ERROR_FORMAT, tostring(index)), 2)
end

function QuaternionSpring.__newindex(self: QuaternionSpring, index: string, value: any)
	local now = self._clock()
	if index == "Position" or index == "p" then
		local _, velocity = _positionVelocity(self, now)
		self._position = value
		self._velocity = velocity
		self._time = now
	elseif index == "Velocity" or index == "v" then
		local position, _ = _positionVelocity(self, now)
		self._position = position
		self._velocity = value
		self._time = now
	elseif index == "Target" or index == "t" then
		local position, velocity = _positionVelocity(self, now)
		self._position = position
		self._velocity = velocity
		self._target = value
		self._time = now
	elseif index == "Damping" or index == "d" then
		local position, velocity = _positionVelocity(self, now)
		self._position = position
		self._velocity = velocity
		self._damping = value
		self._time = now
	elseif index == "Speed" or index == "s" then
		local position, velocity = _positionVelocity(self, now)
		self._position = position
		self._velocity = velocity
		self._speed = value < 0 and 0 or value
		self._time = now
	elseif index == "Clock" then
		local position, velocity = _positionVelocity(self, now)
		self._position = position
		self._velocity = velocity
		self._clock = value
		self._time = value()
	else
		error(string.format(ERROR_FORMAT, tostring(index)), 2)
	end
end


return QuaternionSpring

