#include "composite_layer.h"

CompositeLayer::CompositeLayer() {}
CompositeLayer::CompositeLayer(std::vector<std::unique_ptr<VisualLayer>> layers) : visual_layers(std::move(layers)) {}

void CompositeLayer::draw(SDL_Renderer * const renderer, const SignalBox & signal_box) {
    for (const auto & layer : visual_layers) {
        layer->draw(renderer, signal_box);
    }
