import Engine

engine = Engine.Engine()
engine.initialize_graphics_subsystem()
pos = Engine.Vec2(4,5)
vel = Engine.Vec2(6,7)
tran = Engine.TransformComponent(pos, vel)
print("Position: ", pos)
print("Velocity: ", vel)
print("Transformer: ", tran.get_XPosition(), tran.get_YPosition())
sprite = Engine.SpriteComponent("./assets/BGSky.jpg", Engine.Vec2(0,0), 200, 100)
engine.start()
itr = 0
while itr < 10000:
    sprite.render()
engine.shutdown()

##Shift main loop outside engine and into python
##Let controller take in an input key and an function object
##Complete the sprite class
##Double check pybinding to make sure references are returned correctly
##Circular referencing of game object and sprite components
##Decouple transform from sprite
##In update function of sprite, the user should not have to worry about
##The sprite sheet at all. Instead, the only thing the user should be
##able to control is the frame
##src rectangle in sprite needs more work

