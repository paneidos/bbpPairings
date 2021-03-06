/*
 * This file is part of BBP Pairings, a Swiss-system chess tournament engine
 * Copyright (C) 2016  Jeremy Bierema
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 3.0, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef VERTEXSIG_H
#define VERTEXSIG_H

#include <vector>

#include "blossomsig.h"
#include "types.h"

namespace matching
{
  namespace detail
  {
    template <typename>
    class Graph;

    /**
     * A class representing a blossom or subblossom that is a vertex in the
     * original matching graph.
     */
    template <typename edge_weight>
    struct Vertex final : public Blossom<edge_weight>
    {
      /**
       * The weights of the edges to the other vertices, indexed by vertexIndex.
       */
      typename edge_weight_traits<edge_weight>::vector edgeWeights;
      typename edge_weight_traits<edge_weight>::vector::reference dualVariable;
      /**
       * If this Vertex is not OUTER, this is the minimum resistance of edges
       * between this Vertex and other Vertexes that are OUTER, or
       * graph.aboveMaxEdgeWeight if no such Vertex exists.
       *
       * Only valid during augmentation.
       */
      edge_weight minOuterEdgeResistance;
      /**
       * If this Vertex is not OUTER, this is the Vertex associated with the
       * minimum-resistance edge to an OUTER Vertex, assuming such a Vertex
       * exists.
       *
       * Only valid during augmentation.
       */
      Vertex<edge_weight> *minOuterEdge;
      /**
       * A pointer to the next Vertex in the RootBlossom's linked list of
       * Vertexes.
       */
      Vertex<edge_weight> *nextVertex{ };
      const vertex_index vertexIndex;

      Vertex(vertex_index, Graph<edge_weight> &);

      void resistance(edge_weight &, const Vertex<edge_weight> &) const;
      edge_weight resistance(const Vertex<edge_weight> &) const;
    };
  }
}

#endif
