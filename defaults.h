#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <glm/glm.hpp>

namespace BASE {
    const glm::vec2 ZERO_VEC2(0.0);
    const glm::vec3 ZERO_VEC3(0.0);
    const glm::vec4 ZERO_VEC4(0.0);
}

namespace CONTROLL {
    const int HEIGHT   = 30;
    const int MARGIN_X = 10;
};

namespace BUTTON {
    const int X_MARGIN = 5;
    const int Y_MARGIN = 10;
    const int Y_MARGINBTN_TEXT_MEDIUM = 20;

    const int DEFAULT_WIDTH   = 80;
    const int DEFAULT_HEIGHT = 40;

    const float ALPHA_IMAGE_ENABLED  = 1.0f;
    const float ALPHA_IMAGE_DISABLED = 0.3f;

    const glm::vec3 COLOR_DEFAULT_IMAGE = {1.0, 1.0, 1.0};
    const glm::vec3 COLOR_DEFAULT_TEXT  = {1.0, 1.0, 1.0};
};

namespace LABEL {
    const glm::vec4 COLOR_TEXT = glm::vec4(0.0);
    const glm::vec4 COLOR_BACKGROUND = glm::vec4(0.8,0.8, 0.8, 1.0);
    const int MARGIN_X  = 2;
    const int MARGIN_Y  = 10;
}

namespace TEXT {
    const float SCALE_SMALL = 1.0f;
    const float SCALE_MEDIUM = 1.5f;
    const float SCALE_BIG = 2.0f;

    const float ALPHA_ENABLED = 1.0f;
    const float ALPHA_DISABLED = 0.3f;
}

namespace TERRAIN {
    //Defaults
    //Abstand zwischen den verts
    const float RASTER_X = 10.0f;
    const float RASTER_Z = 10.0f;

    // Auflösung in x und y Richtung:
    const int PATCH_X = 32;
    const int PATCH_Z = 32;
}

#endif // DEFAULTS_H
