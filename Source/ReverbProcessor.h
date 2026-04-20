#pragma once

#include <JuceHeader.h>

class ReverbProcessor : public foleys::MagicProcessor
{
public:
    ReverbProcessor();
    ~ReverbProcessor() override = default;

    bool isBusesLayoutSupported (const juce::AudioProcessor::BusesLayout& layouts) const override;
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void releaseResources() override;

private:
    cgo::Reverb::Params parameters;
    juce::AudioProcessorValueTreeState vts;
    cgo::Reverb reverb;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbProcessor)
};
