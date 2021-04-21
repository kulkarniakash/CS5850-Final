import Engine

# Bug in pybind: don't do this: obj.add_transform_component(Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10)))
# do this: obj.add_transform_component(tran)
# where the argument value is stored in another variable
engine = Engine.Engine()
engine.initialize_graphics_subsystem()



class Sky(Engine.PlayerObject):
    def __init__(self, name):
        super().__init__(name)

    def sprite_init(self):
        dest = Engine.Rect()
        src = Engine.Rect()
        dest.x , dest.y, dest.w, dest.h = 0, 0, 100, 150
        src.x, src.y, src.w, src.h = 0, 0, -1, -1
        self.sprite = Engine.SpriteComponent("./assets/biden.jpg", dest, src)
        super().add_sprite_component(self.sprite)
        
sky = Sky("sky")
sky.sprite_init()

def go_up(obj):
    obj.update_velocity(Engine.Vec2(0, -1))
    obj.update()

def go_down(obj):
    obj.update_velocity(Engine.Vec2(0, 1))
    obj.update()

def go_right(obj):
    obj.update_velocity(Engine.Vec2(1, 0))
    obj.update()

def go_left(obj):
    obj.update_velocity(Engine.Vec2(-1, 0))
    obj.update()

tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10))
sky.add_transform_component(tran)
control = Engine.ControllerComponent()
control.add_input_binding("W", go_up)
control.add_input_binding("S", go_down)
control.add_input_binding("A", go_left)
control.add_input_binding("D", go_right)

sky.add_controller_component(control)

##obj = Engine.GameObject("sky")
##obj.add_sprite_component(sprite)
##tran = Engine.TransformComponent(Engine.Vec2(0,0), Engine.Vec2(5,10))
##obj.add_transform_component(tran)

engine.add_player_object(sky)
engine.start()


while not engine.program_ended():
    engine.input()
    engine.update()
    engine.clear()
    engine.render()
    engine.delay(20)
engine.shutdown()

