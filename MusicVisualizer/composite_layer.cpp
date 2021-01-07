#include "composite_layer.h"

CompositeLayer::CompositeLayer() {}
CompositeLayer::CompositeLayer(std::deque<std::unique_ptr<VisualLayer>> layers) : visual_layers(std::move(layers)) {}

void CompositeLayer::draw(SDL_Renderer * const renderer, const SignalBox & signal_box) {
    for (const auto & layer : visual_layers) {
        layer->draw(renderer, signal_box);
    }
}

void CompositeLayer::add_layer(std::unique_ptr<VisualLayer> layer) {
    visual_layers.push_back(std::move(layer));
}
