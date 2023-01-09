#pragma once

#include <memory>
#include <deque>

#include "visual_layer.h"

// Generic composite class for holding and drawing multiple layers.
class CompositeLayer : public virtual VisualLayer {
public:
    // CompositeLayer constructor which does not initialize layers.
    CompositeLayer();
    // CompositeLayer constructor which initializes layers
    // param: layers - the layers to use
    CompositeLayer(std::deque<std::unique_ptr<VisualLayer>> layers);

    // Add a new layer to the composition.
    // param: layer - the layer to add
    void add_layer(std::unique_ptr<VisualLayer> layer);

    // Clear the existing layers.
    void clear_layers();

    // Draw the CompositeLayer.
    // param: renderer                  - the renderer to draw the CompositeLayer
    // param: signal                    - the signal to draw
    virtual void draw(SDL_Renderer * const renderer, const wave & signal) override;

protected:
    // The visual layers that this layer is composed of.
    std::deque<std::unique_ptr<VisualLayer>> m_visual_layers;
};
