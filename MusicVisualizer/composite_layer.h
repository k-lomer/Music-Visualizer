#pragma once

#include <memory>

#include "visual_layer.h"

// Generic composite class for holding and drawing multiple layers
class CompositeLayer : public virtual VisualLayer {
public:
    // Default contrustor does not initialize layers
    CompositeLayer();
    // Constructor which initializes layers
    // param: layers - the layers to use 
    CompositeLayer(std::vector<std::unique_ptr<VisualLayer>> layers);


    virtual void draw(SDL_Renderer * const renderer, const SignalBox & signal_box) override;

protected:
    std::vector<std::unique_ptr<VisualLayer>> visual_layers;
};
