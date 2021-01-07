#pragma once

#include <memory>
#include <deque>

#include "visual_layer.h"

// Generic composite class for holding and drawing multiple layers
class CompositeLayer : public virtual VisualLayer {
public:
    // Default contrustor does not initialize layers
    CompositeLayer();
    // Constructor which initializes layers
    // param: layers - the layers to use 
    CompositeLayer(std::deque<std::unique_ptr<VisualLayer>> layers);

    // Add a new layer to the composition
    // param: layer - the layer to add
    void add_layer(std::unique_ptr<VisualLayer> layer);

    virtual void draw(SDL_Renderer * const renderer, const SignalBox & signal_box) override;


protected:
    std::deque<std::unique_ptr<VisualLayer>> visual_layers;
};
