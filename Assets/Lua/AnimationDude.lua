local AnimationDude = {}

local animationScene = LoadScene("Assets/Animation/Run1.BVH");

local animationObject = BasicAnimation(animationScene["Animation"][1], animationScene["RootNode"]);


return AnimationDude;

