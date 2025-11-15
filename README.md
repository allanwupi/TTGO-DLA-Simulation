Diffusion-limited aggregation (DLA) simulation
===

Simulate randomly walking particles and growth of Brownian trees using the LILYGO T-Display S3.

See the information at [rosettacode.org](https://rosettacode.org/wiki/Brownian_tree) and the [Wikipedia article](https://en.wikipedia.org/wiki/Diffusion-limited_aggregation).

Current implementation
---

1. Seed is placed at the centre of the screen
2. Particle spawned at a random angle, initial circular radius 3
3. Walk particle randomly until it sticks to the seed (Moore neighbourhood)
4. Repeat from step 2

Limitations and planned features
---

The current simulation is very, very slow. Also, it could look a bit prettier.

1. Add a 'gravity' force that attracts particles towards the centre
2. Support multiple particles moving about simultaneously
3. Draw decaying trails to show the Brownian motion of the particles
4. Rescale screen dynamically as the size of the tree increases
