import Engine

# Bug in pybind: don't do this: obj.add_transform_component(Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10)))
# do this: obj.add_transform_component(tran)
# where the argument value is stored in another variable
engine = Engine.Engine()
engine.initialize_graphics_subsystem()



class Sky(Engine.GameObject):
    def __init__(self, name):
        super().__init__(name)

    def sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 0, 0, 100, 300
        src.x, src.y, src.w, src.h = 0, 0, -1, -1
        self.sprite = Engine.SpriteComponent("./assets/BGSky.jpg", dest, src)
        super().add_sprite_component(self.sprite)
        
sky = Sky("sky")
sky.sprite_init()
    
##sky.sprite_init()

tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10))
sky.add_transform_component(tran)

##obj = Engine.GameObject("sky")
##obj.add_sprite_component(sprite)
##tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10))
##obj.add_transform_component(tran)

class Character(Engine.GameObject):
    def __init__(self, name):
        super().__init__(name)

    def character_sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 0, 0, 100, 200
        src.x, src.y, src.w, src.h = 0, 0, 50, 37
        rows, cols = 16, 7
        self.character_sprite = Engine.CharacterSpriteComponent("./assets/adventurer.jpg", dest, src, rows, cols)
        self.character_sprite.add_animation("idle", 0, 3)
        super().add_character_sprite_component(self.character_sprite)
        
    def update_animation(self):
        self.character_sprite.perform_animation("idle", True)

character = Character("character")
character.character_sprite_init()
character.update_animation()

tran2 = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(0, 0))
character.add_transform_component(tran2)

engine.add_game_object(sky)
engine.add_game_object(character)
engine.start()

while not engine.program_ended():
    engine.input()
    sky.update()
    character.update()
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

