#pragma once
#include <TemplateTest/Fractures/Family.hpp>
#include <TemplateTest/Fractures/Fracture.hpp>
#include <TemplateTest/Random/Sampler2d.hpp>
#include <memory>
#include <vector>

namespace Fractures {
class Factory {
public:
    virtual ~Factory() = default;

    void registerFamily(std::unique_ptr<Family> family,
                        std::shared_ptr<Sampler2d> sampler,
                        double numberDensity);

    // returns a single fracture where the probability of each family is
    // proportional to its number density * area
    std::unique_ptr<Fracture> createFracture() const;

    // returns n = sum_i (numberDensity_i * area_i) fractures
    virtual std::vector<std::unique_ptr<Fracture>> createFractures() const;

    // returns n fractures with probabilities proportional to numberDensity_i *
    // area_i
    virtual std::vector<std::unique_ptr<Fracture>> createFractures(
        uint32_t n) const;

    std::vector<std::string> getFamilyIdNames() const;

protected:
    struct RegisteredFamily {
        std::unique_ptr<Family> family;
        std::shared_ptr<Sampler2d> sampler;
        double numberDensity;
    };

    // get a random family according to number density
    std::size_t getRandomFamilyIdx() const;

    // std::unordered_map<std::string, RegisteredFamily> m_families;
    std::vector<RegisteredFamily> m_families;
};

class RejectionSamplingAABBFactory : public Factory {
public:
    // returns n = sum_i (numberDensity_i * area_i) fractures
    std::vector<std::unique_ptr<Fracture>> createFractures() const override;

    // returns n fractures with probabilities proportional to numberDensity_i *
    // area_i
    std::vector<std::unique_ptr<Fracture>> createFractures(
        uint32_t n) const override;
};
}  // namespace Fractures
