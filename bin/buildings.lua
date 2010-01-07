buildings = {
    {
        name = "Statue of Liberty",
        tex = {
            path = "gfx/buildings/statue.png",
            --x and y defaults to 0
            x = 0,  y = 1,
            w = 60, h = 179,
        },
        coll_box = {
            w = 60, h = 179,
        },
        layers = { 2 },
    },
    
    {
        name = "Police",
        tex = {
            path = "gfx/buildings/bpolice.png" ,
            x = 0,  y = 1,
            w = 62, h = 58
        },
        coll_box = {
            w = 62, h = 59
        },
        layers = { 0 },
        --a clear Z label
        z_labels = { 
            { x = 17, y = 54, color = 0xff5b5b5b },
        },
        
        --sets possible camera positions
        --if active they're active from the start
        --else they're just possible positions for future cams
        cams = {
            { x = 6, y = 47, color = 0xff000000, direction = -1, is_active = true },
            { x = 34, y = 51, color = 0xff000000, direction = 1, is_active = true },
        },
    },
    
    {
        name = "Prison",
        tex = {
            path = "gfx/buildings/bprison.png" ,
            x = 0,  y = 1,
            w = 137, h = 44
        },
        coll_box = {
            w = 137, h = 45
        },
        layers = { 0 },
        z_labels = { 
            { x = 119, y = 39, color = 0xff5b5b5b },
        },
        prison_bars = {
            { x = 10,  y = 40, color = 0xff555555 },
            { x = 20, y = 40, color = 0xff555555 },
            { x = 35, y = 40, color = 0xff555555 },
            { x = 45, y = 40, color = 0xff555555 },
        },
    },
    
    {
        name = "School",
        tex = {
            path = "gfx/buildings/bschool.png",
            x = 0,  y = 1,
            w = 68, h = 67
        },
        coll_box = {
            w = 68, h = 68
        },
        layers = { 0 },
        z_labels = { 
            { x = 51, y = 61, color = 0xff5b5b5b },
        },
        prison_bars = {
            { x = 10, y = 52, color = 0xff555555 },
            { x = 10, y = 60, color = 0xff555555 },
        },
    },
    
    {
        name = "Hospital",
        tex = {
            path = "gfx/buildings/bhospital.png",
            x = 0,  y = 1,
            w = 46, h = 50,
        },
        coll_box = {
            w = 46, h = 51
        },
        layers = { 0 },
        z_labels = { 
            { x = 20, y = 45, color = 0xff5b5b5b },
        },
        graves = {
            color = 0xff000000,
            used = 10,
            { x = 0,  y = 5 },
            { x = 11, y = 5 },
            { x = 37, y = -8 },
            { x = 33, y = -14 },
            { x = 28, y = 14 },
            { x = 31, y = 0 },
            { x = 38, y = -22 },
            { x = 7,  y = -16 },
            { x = 3,  y = -10 },
            { x = 12,  y = 15 },
            { x = -2, y = 15 },
        },
    },
    
    {
        name = "Star of Hope",
        tex = {
            path = "gfx/buildings/starbuilding.png",
            --x and y defaults to 0
            x = 0,  y = 1,
            w = 80, h = 219,
        },
        coll_box = {
            w = 80, h = 220,
        },
        layers = { 3 },
        z_labels = { 
            { x = 54,  y = 200, color = 0xff4a4a4a },
        },
        --set how many can live in the building
        room = 2000,
    },
    
    {
        name = "Nuclear",
        tex = {
            path = "gfx/buildings/nuclear.png",
            --x and y defaults to 0
            x = 0,  y = 1,
            w = 160, h = 122,
        },
        coll_box = {
            w = 160, h = 123,
        },
        layers = { 3 },
        z_labels = { 
            { x = 56,  y = 116, color = 0xff4a4a4a },
            { x = 116, y = 116, color = 0xff4a4a4a },
        },
    },
    
    {
        name = "Random big thing",
        tex = {
            path = "gfx/buildings/bigbuild.png",
            --x and y defaults to 0
            x = 0,  y = 1,
            w = 80, h = 144,
        },
        coll_box = {
            w = 80, h = 145,
        },
        layers = { 3 },
        room = 500,
    },
    
    {
        name = "Hideout",
        tex = {
            --omit path and you'll get a nice square
            w = 20, h = 40,
            --will be colored to fit the layer
            use_layer_color = true,
        },
        coll_box = {
            w = 20, h = 40,
        },
        layers = { 1, 2, 3 },
        room = 50,
    },
    
    {
        name = "Crack Joint",
        tex = {
            --omit path and you'll get a nice square
            w = 20, h = 60,
            --will be colored to fit the layer
            use_layer_color = true,
        },
        coll_box = {
            w = 20, h = 60,
        },
        layers = { 1, 2, 3 },
        room = 80,
    },
    
    {
        name = "Gate to Heaven",
        tex = {
            w = 20, h = 80,
            use_layer_color = true,
        },
        coll_box = {
            w = 20, h = 80,
        },
        layers = { 1, 2, 3 },
        room = 140,
    },
    
    {
        name = "Zed's Tribute",
        tex = {
            w = 20, h = 100,
            use_layer_color = true,
        },
        coll_box = {
            w = 20, h = 100,
        },
        layers = { 1, 2, 3 },
        room = 200,
    },
}
