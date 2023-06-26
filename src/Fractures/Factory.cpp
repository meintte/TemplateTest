#include <TemplateTest/Fractures/Factory.hpp>

namespace Fractures {
void Factory::registerFamily(std::unique_ptr<Family> family,
                             std::shared_ptr<Sampler2d> sampler,
                             double numberDensity) {
    // currently overwrites if already exists
    // TODO: maybe combine sampler and numberDensity with the existing ones?
    m_families.push_back(
        {std::move(family), std::move(sampler), numberDensity});
}

std::unique_ptr<Fracture> Factory::createFracture() const {
    if (m_families.empty()) {
        return nullptr;
    }

    const auto& [family, sampler, numberDensity] =
        m_families[getRandomFamilyIdx()];

    return family->createFracture(sampler->sample());
}
std::vector<std::unique_ptr<Fracture>> Factory::createFractures() const {
    if (m_families.empty()) {
        throw std::runtime_error("No families registered");
    }

    std::vector<std::unique_ptr<Fracture>> fractures;
    for (const auto& [family, sampler, numberDensity] : m_families) {
        double nf_d = numberDensity * sampler->getArea();
        auto nf = static_cast<uint32_t>(nf_d);
        if (nf_d - nf > Random::nextDouble()) {
            ++nf;
        }

        fractures.reserve(fractures.size() + nf);
        for (uint32_t i = 0; i < nf; ++i) {
            fractures.push_back(family->createFracture(sampler->sample()));
        }
    }

    std::shuffle(fractures.begin(), fractures.end(), Random::getEngine());

    return fractures;
}

std::vector<std::unique_ptr<Fracture>> Factory::createFractures(
    uint32_t n) const {
    if (m_families.empty()) {
        throw std::runtime_error("No families registered");
    }

    std::vector<std::unique_ptr<Fracture>> fractures;
    fractures.reserve(n);
    for (uint32_t i = 0; i < n; ++i) {
        fractures.push_back(createFracture());
    }

    return fractures;
}

std::vector<std::string> Factory::getFamilyIdNames() const {
    std::vector<std::string> names(m_families.size());
    std::transform(m_families.begin(), m_families.end(), names.begin(),
                   [](const auto& reg) { return reg.family->getIdName(); });
    return names;
}

std::size_t Factory::getRandomFamilyIdx() const {
    // TODO: maybe cache this? (create an init function that precomputes this)
    std::vector<double> numFracs(m_families.size());

    std::size_t idx = 0;
    for (const auto& reg : m_families) {
        numFracs[idx++] = reg.numberDensity * reg.sampler->getArea();
    }
    std::discrete_distribution<std::size_t> dist(numFracs.begin(),
                                                 numFracs.end());
    return dist(Random::getEngine());
}

std::vector<std::unique_ptr<Fracture>> RejectionSamplingAABBFactory::createFractures()
    const {
    if (m_families.empty()) {
        throw std::runtime_error("No families registered");
    }

    std::vector<std::unique_ptr<Fracture>> fractures;
    for (const auto& [family, sampler, numberDensity] : m_families) {
        double nf_d = numberDensity * sampler->getArea();
        auto nf = static_cast<uint32_t>(nf_d);
        if (nf_d - nf > Random::nextDouble()) {
            ++nf;
        }

        fractures.reserve(fractures.size() + nf);

        // Rejection sampling
        constexpr uint32_t maxTries = 1000;
        for (uint32_t i = 0; i < nf; ++i) {
            bool success = false;
            for (uint32_t tries = 0; tries < maxTries; ++tries) {
                auto frac = family->createFracture(sampler->sample());
                const auto& aabb = frac->getAABB();
                // check if new fractures intersects with any of the existing
                // fractures
                if (!std::any_of(fractures.begin(), fractures.end(),
                                 [&aabb](const auto& f) {
                                     return aabb.intersects(f->getAABB());
                                 })) {
                    fractures.push_back(std::move(frac));
                    success = true;
                    break;
                }
            }
            if (!success) {
                throw std::runtime_error("Failed to create fracture after " +
                                         std::to_string(maxTries) + " tries");
            }
        }
    }

    std::shuffle(fractures.begin(), fractures.end(), Random::getEngine());

    return fractures;
}

std::vector<std::unique_ptr<Fracture>> RejectionSamplingAABBFactory::createFractures(
    uint32_t n) const {
    if (m_families.empty()) {
        throw std::runtime_error("No families registered");
    }

    std::vector<std::unique_ptr<Fracture>> fractures;
    fractures.reserve(n);

    // Rejection sampling
    constexpr uint32_t maxTries = 1000;
    for (uint32_t i = 0; i < n; ++i) {
        bool success = false;
        for (uint32_t tries = 0; tries < maxTries; ++tries) {
            auto frac = createFracture();
            const auto& aabb = frac->getAABB();
            // check if new fractures intersects with any of the existing
            // fractures
            if (!std::any_of(fractures.begin(), fractures.end(),
                             [&aabb](const auto& f) {
                                 return aabb.intersects(f->getAABB());
                             })) {
                fractures.push_back(std::move(frac));
                success = true;
                break;
            }
        }
        if (!success) {
            throw std::runtime_error("Failed to create fracture after " +
                                     std::to_string(maxTries) + " tries");
        }
    }

    return fractures;
}

}  // namespace Fractures
