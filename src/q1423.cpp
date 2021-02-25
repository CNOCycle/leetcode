//https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/

int maxScore(vector<int>& cardPoints, int k)
{
    int sum = 0;
    for(int ii=1;ii<=k;ii=ii+1)
    {
        sum = sum + cardPoints[ii-1];
    }


    int max = sum;
    for(int ii=1;ii<=k;ii=ii+1)
    {
        sum = sum - cardPoints[k-ii] + cardPoints[cardPoints.size()-ii];
        if(sum > max)
        {
            max = sum;
        }

    }

    return max;
};
