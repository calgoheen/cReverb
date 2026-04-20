#include "ReverbProcessor.h"

ReverbProcessor::ReverbProcessor()
    : foleys::MagicProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                               .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
    vts (*this, nullptr, "PARAMS", { parameters.predelay.release(),
                                     parameters.size.release(),
                                     parameters.decay.release(),
                                     parameters.inputFilterLowpassCutoff.release(),
                                     parameters.inputFilterHighpassCutoff.release(),
                                     parameters.diffusionModRate.release(),
                                     parameters.diffusionModDepth.release(),
                                     parameters.tailFilterLowCutoff.release(),
                                     parameters.tailFilterLowGain.release(),
                                     parameters.tailFilterHighCutoff.release(),
                                     parameters.tailFilterHighGain.release(),
                                     parameters.tailModRate.release(),
                                     parameters.tailModDepth.release(),
                                     parameters.earlyReflectionGain.release(),
                                     parameters.diffusionGain.release(),
                                     parameters.mix.release() }),
    reverb (parameters)
{
    magicState.setGuiValueTree (BinaryData::layout_xml, BinaryData::layout_xmlSize);
}

bool ReverbProcessor::isBusesLayoutSupported (const juce::AudioProcessor::BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void ReverbProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    reverb.prepareToPlay (sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void ReverbProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;
    reverb.processBlock (buffer, midi, getPlayHead());
}

void ReverbProcessor::releaseResources()
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReverbProcessor();
}
