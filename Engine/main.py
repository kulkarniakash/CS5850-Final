import Engine

# Bug in pybind: don't do this: obj.add_transform_component(Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10)))
# do this: obj.add_transform_component(tran)
# where the argument value is stored in another variable
engine = Engine.Engine()
engine.initialize_graphics_subsystem()

dest = Engine.Rect()
src = Engine.Rect()
dest.x , dest.y, dest.w, dest.h = 0, 0, 100, 300
src.x, src.y, src.w, src.h = 0, 0, -1, -1
sprite = Engine.SpriteComponent("./assets/BGSky.jpg", dest, src)

obj = Engine.GameObject("sky")
obj.add_sprite_component(sprite)
tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10))
obj.add_transform_component(tran)
engine.add_game_object(obj)
engine.start()


while not engine.program_ended():
    engine.input()
    obj.update()
    engine.clear()
    engine.render()
    engine.delay(20)
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

