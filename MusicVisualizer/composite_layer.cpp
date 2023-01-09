#include "composite_layer.h"

CompositeLayer::CompositeLayer() {}
CompositeLayer::CompositeLayer(std::deque<std::unique_ptr<VisualLayer>> layers) : m_visual_layers(std::move(layers)) {}

void CompositeLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    for (const auto & layer : m_visual_layers) {
        layer->draw(renderer, signal);
    }
}

void CompositeLayer::add_layer(std::unique_ptr<VisualLayer> layer) {
    m_visual_layers.push_back(std::move(layer));
}

void CompositeLayer::clear_layers() {
    m_visual_layers.clear();
}
