import Engine

# Bug in pybind: don't do this: obj.add_transform_component(Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10)))
# do this: obj.add_transform_component(tran)
# where the argument value is stored in another variable
engine = Engine.Engine()
engine.initialize_graphics_subsystem()

tm = Engine.TileManager(100, 100, Engine.Vec2(0,0))
Engine.TileManager.load_tile_types("./assets/Tiles")
tm.load_level_map("./assets/level1")

camera = Engine.Camera.get_instance()


class Biden(Engine.PlayerObject):
    def __init__(self, name):
        super().__init__(name, 25, 25)
        self.keypressed = {"W": False, "A": False, "S": False, "D": False}
        self.speed = 3

    def sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 0, 0, 25, 35
        src.x, src.y, src.w, src.h = 0, 0, -1, -1
        self.tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(0,0))
        super().add_transform_component(self.tran)
        self.sprite = Engine.SpriteComponent("./assets/biden.jpg", src)
        super().add_sprite_component(self.sprite)
        

class Sky(Engine.GameObject):
    def __init__(self, name):
        super().__init__(name, 100, 100)

    def sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 200, 300, 100, 150
        src.x, src.y, src.w, src.h = 0, 0, -1, -1
        self.tran = Engine.TransformComponent(Engine.Vec2(200,300), Engine.Vec2(0,0))
        super().add_transform_component(self.tran)
        self.sprite = Engine.SpriteComponent("./assets/BGSky.jpg", src)
        super().add_sprite_component(self.sprite)
        
        
biden = Biden("biden")
sky = Sky("sky")
biden.sprite_init()
sky.sprite_init()

def go_up(obj):
    obj.update_velocity(Engine.Vec2(0, -obj.speed))
##    obj.update()

def go_down(obj):
    obj.update_velocity(Engine.Vec2(0, obj.speed))
##    obj.update()

def go_right(obj):
    obj.update_velocity(Engine.Vec2(obj.speed, 0))
##    obj.update()

def go_left(obj):
    obj.update_velocity(Engine.Vec2(-obj.speed, 0))
##    obj.update()

def radial_gravity(obj):
    w = obj.get_sprite_component().get_width()
    h = obj.get_sprite_component().get_height()
    pos = obj.get_transform_component().get_position()
    obj.update_velocity( Engine.Vec2(0.005 *(250 - pos.x - w / 2), 0.005 *(375 - pos.y - h / 2)))

def gravity(obj):
    obj.update_velocity(Engine.Vec2(0, 1))

control = Engine.ControllerComponent()
control.add_input_binding("W", go_up, False)
control.add_input_binding("S", go_down, False)
control.add_input_binding("A", go_left, False)
control.add_input_binding("D", go_right, False)
##control.add_input_release_binding("W", key_release_w)
##control.add_input_release_binding("S", key_release_s)
##control.add_input_release_binding("A", key_release_a)
##control.add_input_release_binding("D", key_release_d)


class Character(Engine.PlayerObject):
    def __init__(self, name):
        super().__init__(name, 80, 80)
        self.flipped = False
        self.speed = 4

    def character_sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 0, 0, 100, 200
        src.x, src.y, src.w, src.h = 0, 0, 50, 37
        rows, cols = 16, 7
        self.character_sprite = Engine.CharacterSpriteComponent("./assets/adventurer.jpg", src, rows, cols)
        self.tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(0,0))
        super().add_transform_component(self.tran)
        self.character_sprite.add_animation("idle", 0, 3)
        self.character_sprite.add_animation("run", 8, 13)
        self.character_sprite.add_animation("jump", 15, 22)
        self.character_sprite.add_animation("attack", 40, 50)
        super().add_character_sprite_component(self.character_sprite)
    
    def player_go_up(self, obj):
        obj.update_velocity(Engine.Vec2(0, -5*self.speed))


    def player_go_down(self, obj):
        obj.update_velocity(Engine.Vec2(0, self.speed))

    def player_go_right(self, obj):
        self.flipped = False
        obj.update_animation_run(self.flipped, 3)
        obj.update_velocity(Engine.Vec2(self.speed, 0))

    def player_go_left(self, obj):
        self.flipped = True
        obj.update_animation_run(self.flipped, 3)
        obj.update_velocity(Engine.Vec2(-self.speed, 0))

    def player_release_key_up(self, obj):
        self.check_if_no_input()

    def player_release_key_right(self, obj):
        tran = self.get_transform_component()
        obj.update_velocity(Engine.Vec2(-tran.get_velocity().x, 0))
        

    def player_release_key_left(self, obj):
        tran = self.get_transform_component()
        obj.update_velocity(Engine.Vec2(-tran.get_velocity().x, 0))

    def character_controls_init(self):
        self.control2 = Engine.ControllerComponent()
        self.control2.add_input_binding("W", self.player_go_up, False)
        self.control2.add_input_binding("S", self.player_go_down, False)
        self.control2.add_input_binding("D", self.player_go_right, False)
        self.control2.add_input_binding("A", self.player_go_left, False)
        self.control2.add_input_release_binding("W", self.player_release_key_up, True)
        self.control2.add_input_release_binding("S", self.player_release_key_up, True)
        self.control2.add_input_release_binding("D", self.player_release_key_right, False)
        self.control2.add_input_release_binding("A", self.player_release_key_left, False)

        super().add_controller_component(self.control2)
        
    def update_animation_idle(self, flipped, speed):
        self.character_sprite.perform_animation("idle", flipped, speed)

    def update_animation_run(self, flipped, speed):
        self.character_sprite.perform_animation("run", flipped, speed)

    def update_animation_jump(self, flipped, speed):
        self.character_sprite.perform_animation("jump", flipped, speed)

    def update_animation_attack(self, flipped, speed):
        self.character_sprite.perform_animation("attack", flipped, speed)
    
    def check_if_no_input(self):
        if (self.control2.no_key_pressed()):
            character.update_animation_idle(self.flipped, 3)


character = Character("character")
character.character_sprite_init()
character.character_controls_init()

camera.bind_to_object(character)
biden.add_controller_component(control)

##obj = Engine.GameObject("sky")
##obj.add_sprite_component(sprite)
##tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10))
##obj.add_transform_component(tran)

engine.add_player_object(character)
engine.add_UF_callback(gravity)
engine.add_tilemanager(tm)
engine.start()


while not engine.program_ended():
    engine.input()
    engine.update()
    engine.clear()
    engine.render()
    engine.delay(20)
engine.shutdown()

