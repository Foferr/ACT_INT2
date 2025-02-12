#include <gtest/gtest.h>
#include "../src/linear_search.h"

class SearchNearestTest : public ::testing::Test {
protected:
    vector<pair<int, int>> centrals;
};

TEST_F(SearchNearestTest, UbicacionMasCercana_Caso1) {
    centrals = {{0, 0}, {5, 5}, {10, 10}};
    pair<int, int> new_contract = {3, 3};
    EXPECT_EQ(SearchNearest::Find(centrals, new_contract), make_pair(5, 5));
}

TEST_F(SearchNearestTest, UbicacionMasCercana_Caso2) {
    centrals = {{1, 2}, {3, 4}, {6, 8}};
    pair<int, int> new_contract = {4, 5};
    EXPECT_EQ(SearchNearest::Find(centrals, new_contract), make_pair(3, 4));
}

TEST_F(SearchNearestTest, UbicacionMasCercana_Caso3) {
    centrals = {{-5, -5}, {0, 0}, {5, 5}};
    pair<int, int> new_contract = {-3, -3};
    EXPECT_EQ(SearchNearest::Find(centrals, new_contract), make_pair(-5, -5));
}

TEST_F(SearchNearestTest, UbicacionMasCercana_Caso4) {
    centrals = {{100, 100}, {200, 200}, {300, 300}};
    pair<int, int> new_contract = {250, 250};
    EXPECT_EQ(SearchNearest::Find(centrals, new_contract), make_pair(200, 200));
}

TEST_F(SearchNearestTest, ListaVacia) {
    centrals = {};
    pair<int, int> new_contract = {3, 3};
    EXPECT_EQ(SearchNearest::Find(centrals, new_contract), make_pair(0, 0));
}

TEST_F(SearchNearestTest, PuntoExactamenteEnCentral) {
    centrals = {{10, 10}, {20, 20}, {30, 30}};
    pair<int, int> new_contract = {20, 20}; // Ya existe en las centrales
    EXPECT_EQ(SearchNearest::Find(centrals, new_contract), make_pair(20, 20));
}
